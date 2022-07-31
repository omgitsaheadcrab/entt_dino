/**
 * @file      game.cc
 * @brief     Game logic and event loop.
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-02
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#include "core/game.h"

#include <SDL2/SDL.h>

#include <set>

#include <entt/entity/entity.hpp>

#include "core/hud.h"
#include "core/res_manager.h"
#include "core/window.h"
#include "ent/dino.h"
#include "sys/background.h"
#include "sys/despawn.h"
#include "sys/movement.h"
#include "sys/render.h"

Game::Game(const int kWindowWidth, const int kWindowHeight)
    : window_ {"entt_dino", kWindowWidth, kWindowHeight} {
  Init();
}

void Game::Init() {
  dead_ = false;
  over_ = false;
  score_ = 0;
  high_score_ = 0;
  fps_ = 0;
  base_speed_ = 1;
  res_manager_.Init(window_.renderer());
  hud_.Init(&window_, &res_manager_, window_.renderer());
  entities::CreateDino(&registry_, res_manager_, window_.bounds());
  systems::SpawnBackgroundElements(&registry_, res_manager_, &cloud_entities_,
                                   &floor_entities_, window_.bounds());
}

void Game::HandleEvents() {
  SDL_PollEvent(window_.event());

  switch (window_.event()->type) {
    case SDL_QUIT:
      over_ = true;
      break;
    case SDL_KEYDOWN:
      switch (window_.event()->key.keysym.sym) {
        case SDLK_ESCAPE:  // Press ESC to quit
          over_ = true;
          break;
        case SDLK_SPACE:
          base_speed_ += 1;
          score_ += 1;
          break;
        case SDLK_d:
          dead_ = true;
          high_score_ = score_ > high_score_ ? score_ : high_score_;
          break;
        case SDLK_r:
          score_ = 0;
          base_speed_ = 1;
          dead_ = false;
          break;
      }
      break;
    case SDL_MOUSEBUTTONDOWN:
      SDL_Point mouse_position;
      SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
      if (hud_.RetryClicked(&mouse_position)) {
        score_ = 0;
        base_speed_ = 1;
        dead_ = false;
      }
      break;
    default:
      break;
  }
}

void Game::Update() {
  systems::Move(&registry_, base_speed_, dead_);
  std::set<entt::entity> del = systems::Despawn(&registry_);
  for (auto& e : del) {
    floor_entities_.erase(e);
    cloud_entities_.erase(e);
  }
  systems::SpawnBackgroundElements(&registry_, res_manager_, &cloud_entities_,
                                   &floor_entities_, window_.bounds());
  hud_.Update(score_, high_score_, fps_, dead_);
}

void Game::Render() {
  SDL_SetRenderDrawColor(window_.renderer(), 239, 239, 239, 255);
  SDL_RenderClear(window_.renderer());
  systems::RenderSprites(window_.renderer(), &registry_);
  hud_.Draw(dead_);
  SDL_RenderPresent(window_.renderer());
}

void Game::Run() {
  const double kMSPerUpdate {1000.0 / kUpdatesPerSecond_};
  double previous_time = SDL_GetTicks();
  double lag = 0.0;
  int frames = 0;
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
