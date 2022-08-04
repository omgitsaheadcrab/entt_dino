/**
 * @file      game.cc
 * @brief     Game logic and event loop.
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-02
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#include "core/game.h"

#include <SDL2/SDL.h>
#include <spdlog/spdlog.h>

#include <cstdint>
#include <set>

#include <entt/entity/entity.hpp>

#include "comp/state.h"
#include "core/hud.h"
#include "core/res_manager.h"
#include "core/window.h"
#include "ent/dino.h"
#include "sys/despawn.h"
#include "sys/manage.h"
#include "sys/move.h"
#include "sys/render.h"
#include "sys/spawn.h"

Game::Game(const int kWindowWidth, const int kWindowHeight)
    : window_ {"entt_dino", kWindowWidth, kWindowHeight} {
  Init();
}

void Game::Init() {
  over_ = false;
  base_speed_ = 1;
  fps_ = 0;
  high_score_ = 0;
  score_ = 0;
  res_manager_.Init(window_.renderer());
  hud_.Init(&window_, &res_manager_);
  dino_ = entities::CreateDino(&registry_, res_manager_, window_.bounds());
  systems::spawn::Clouds(&registry_, res_manager_, &cloud_entities_,
                         window_.bounds());
  systems::spawn::Floors(&registry_, res_manager_, &floor_entities_,
                         window_.bounds());
}

void Game::HandleEvents() {
  SDL_PollEvent(&window_.event());

  auto dino_state = systems::manage::GetState(&registry_, dino_);

  switch (window_.event().type) {
    case SDL_QUIT:
      over_ = true;
      break;
    case SDL_KEYDOWN:
      switch (window_.event().key.keysym.sym) {
        case SDLK_ESCAPE:  // Press ESC to quit
          over_ = true;
          break;
        case SDLK_SPACE:
          base_speed_ += 1;
          score_ += 1;
          dino_state.jumping = true;
          break;
        case SDLK_d:
          base_speed_ = 0;
          dino_state.dead = true;
          high_score_ = score_ > high_score_ ? score_ : high_score_;
          break;
        case SDLK_r:
          score_ = 0;
          base_speed_ = 1;
          dino_state.dead = false;
          break;
      }
      break;
    case SDL_KEYUP:
      switch (window_.event().key.keysym.sym) {
        case SDLK_SPACE:
          dino_state.jumping = false;
          break;
      }
      break;
    case SDL_MOUSEBUTTONDOWN:
      SDL_Point mouse_position;
      SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
      if (hud_.RetryClicked(mouse_position)) {
        score_ = 0;
        base_speed_ = 1;
        dino_state.dead = false;
      }
      break;
    default:
      break;
  }

  systems::manage::SetState(&registry_, dino_, &dino_state);
}

void Game::Update() {
  systems::move::RigidBodies(&registry_, base_speed_);
  std::set<entt::entity> del = systems::despawn::OutOfBounds(&registry_);
  for (auto& e : del) {
    floor_entities_.erase(e);
    cloud_entities_.erase(e);
  }
  systems::spawn::Clouds(&registry_, res_manager_, &cloud_entities_,
                         window_.bounds());
  systems::spawn::Floors(&registry_, res_manager_, &floor_entities_,
                         window_.bounds());
  auto dino_state = systems::manage::GetState(&registry_, dino_);
  if (dino_state.jumping) {
    SPDLOG_DEBUG("I'm jumping!");
  }
  hud_.Update(score_, high_score_, fps_, dino_state.dead);
}

void Game::Render() {
  SDL_SetRenderDrawColor(window_.renderer(), 239, 239, 239, 255);
  // SDL_SetRenderDrawColor(window_.renderer(), 16, 16, 16, 255);
  SDL_RenderClear(window_.renderer());
  auto dino_state = systems::manage::GetState(&registry_, dino_);
  systems::render::Sprites(window_.renderer(), &registry_);
  hud_.Draw(dino_state.dead);
  SDL_RenderPresent(window_.renderer());
}

void Game::Run() {
  const double kMSPerUpdate {1000.0 / kUpdatesPerSecond_};
  double previous_time = SDL_GetTicks();
  double lag = 0.0;
  uint32_t frames = 0;
  double frames_elapsed = 0.0;

  while (!over_) {
    double current_time = SDL_GetTicks();
    double elapsed = current_time - previous_time;
    previous_time = current_time;
    lag += elapsed;
    frames_elapsed += elapsed;

    // HandleEvents as often as possible
    HandleEvents();

    // Update only once per kMSPerUpdate
    while (lag >= kMSPerUpdate) {
      Update();
      lag -= kMSPerUpdate;
    }

    // Render as often as possible
    Render();
    frames++;

    // Frame rate counter (updates every 250ms)
    if (frames_elapsed > 250.0) {
      fps_ = static_cast<double>(frames) / (frames_elapsed / 1000.0);
      frames = 0;
      frames_elapsed = 0.0;
    }
  }
}
