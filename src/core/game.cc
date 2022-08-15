/**
 * @file      game.cc
 * @brief     Game logic and event loop
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-02
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#include "core/game.h"

#include <SDL2/SDL.h>

#include <cstdint>

#include <entt/entity/entity.hpp>

#include "SDL_events.h"
#include "SDL_video.h"
#include "core/hud.h"
#include "core/res_manager.h"
#include "core/window.h"
#include "ctx/game.h"
#include "ctx/graphics.h"
#include "ent/dino.h"
#include "ent/entity_spawner.h"
#include "sys/despawn.h"
#include "sys/move.h"
#include "sys/render.h"
#include "sys/spawn.h"
#include "sys/sync.h"

Game::Game(const int kWindowWidth, const int kWindowHeight)
    : window_ {"entt_dino", kWindowWidth, kWindowHeight} {
  Init();
}

void Game::Init() {
  dead_ = false;
  res_manager_.Init(window_.renderer());

  contexts::graphics::SetFPS(&registry_, 0);
  contexts::game::SetOver(&registry_, false);
  contexts::game::SetSpeed(&registry_, 1);
  contexts::game::SetHighscore(&registry_, 0);
  contexts::game::SetScore(&registry_, 0);
  over_ = false;
  hud_.Init(&window_, &res_manager_);
  contexts::graphics::SetBounds(&registry_, window_.window());
  entities::CreateDino(&registry_, res_manager_);
  entities::CreateCloudSpawner(&registry_, 2);
  entities::CreateFloorSpawner(&registry_, 3);
}

void Game::HandleEvents() {
  SDL_PollEvent(&window_.event());

  uint32_t score, high_score;

  switch (window_.event().type) {
    case SDL_QUIT:
      contexts::game::SetOver(&registry_, true);
      over_ = true;
      break;
    case SDL_WINDOWEVENT:
      contexts::graphics::SetBounds(&registry_, window_.window());
      break;
    case SDL_KEYDOWN:
      switch (window_.event().key.keysym.sym) {
        case SDLK_ESCAPE:  // Press ESC to quit
          contexts::game::SetOver(&registry_, true);
          over_ = true;
          break;
        case SDLK_SPACE:
          contexts::game::IncrementSpeed(&registry_);
          contexts::game::IncrementScore(&registry_);
          break;
        case SDLK_d:
          contexts::game::SetSpeed(&registry_, 0);
          dead_ = true;
          score = contexts::game::GetScore(&registry_).value;
          high_score = contexts::game::GetHighscore(&registry_).value;
          high_score = score > high_score ? score : high_score;
          contexts::game::SetHighscore(&registry_, high_score);
          break;
        case SDLK_r:
          contexts::game::SetScore(&registry_, 0);
          contexts::game::SetSpeed(&registry_, 1);
          dead_ = false;
          break;
      }
      break;
    case SDL_KEYUP:
      switch (window_.event().key.keysym.sym) {
        case SDLK_SPACE:
          break;
      }
      break;
    case SDL_MOUSEBUTTONDOWN:
      SDL_Point mouse_position;
      SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
      if (hud_.RetryClicked(mouse_position)) {
        contexts::game::SetScore(&registry_, 0);
        contexts::game::SetSpeed(&registry_, 1);
        dead_ = false;
      }
      break;
    default:
      break;
  }
}

void Game::Update() {
  systems::move::RigidBodies(&registry_);
  systems::spawn::Floors(&registry_, res_manager_);
  systems::spawn::Clouds(&registry_, res_manager_);
  systems::despawn::OutOfBounds(&registry_);
  systems::sync::Transforms(&registry_);
  hud_.Update(&registry_, dead_);
}

void Game::Render() {
  SDL_SetRenderDrawColor(window_.renderer(), 239, 239, 239, 255);
  // SDL_SetRenderDrawColor(window_.renderer(), 16, 16, 16, 255);
  SDL_RenderClear(window_.renderer());
  systems::render::Sprites(window_.renderer(), &registry_);
  hud_.Draw(dead_);
  SDL_RenderPresent(window_.renderer());
}

void Game::Run() {
  const double kMSPerUpdate {1000.0 / kUpdatesPerSecond_};
  double previous_time = SDL_GetTicks();
  double lag = 0.0;
  uint32_t fps;
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
      fps = static_cast<double>(frames) / (frames_elapsed / 1000.0);
      contexts::graphics::SetFPS(&registry_, fps);
      frames = 0;
      frames_elapsed = 0.0;
    }
  }
}
