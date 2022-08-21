/**
 * @file      game.cc
 * @brief     Game logic and event loop
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-02
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#include "core/game.h"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>

#include <cstdint>

#include <entt/entity/entity.hpp>

#include "core/colors.h"
#include "core/hud.h"
#include "core/res_manager.h"
#include "core/window.h"
#include "ctx/game_states.h"
#include "ctx/graphics.h"
#include "ent/dino.h"
#include "ent/entity_spawner.h"
#include "sys/despawn.h"
#include "sys/move.h"
#include "sys/render.h"
#include "sys/spawn.h"
#include "sys/sync.h"

Game::Game(const int kWindowWidth, const int kWindowHeight)
    : window_ {"entt_dino", kWindowWidth, kWindowHeight} {}

void Game::Init() {
  contexts::graphics::SetFPS(&registry_, 0);
  contexts::game_states::SetSpeed(&registry_, 1.0);
  contexts::game_states::SetScore(&registry_, 0);
  contexts::game_states::SetHighscore(&registry_, 0);
  contexts::graphics::SetBounds(&registry_, window_.window());

  res_manager_.Init(window_.renderer());
  hud_.Init(&registry_, window_.renderer(), &res_manager_);

  entities::dino::Create(&registry_, res_manager_);
  entities::CreateCloudSpawner(&registry_, 2);
  entities::CreateFloorSpawner(&registry_, 3);
}

void Game::HandleEvents() {
  SDL_PollEvent(&window_.event());

  uint32_t score, high_score;

  switch (window_.event().type) {
    case SDL_QUIT:
      contexts::game_states::SetOver(&registry_, true);
      break;
    case SDL_WINDOWEVENT:
      contexts::graphics::SetBounds(&registry_, window_.window());
      break;
    case SDL_KEYDOWN:
      switch (window_.event().key.keysym.sym) {
        case SDLK_ESCAPE:  // Press ESC to quit
          contexts::game_states::SetOver(&registry_, true);
          break;
        case SDLK_SPACE:
          contexts::game_states::IncrementSpeed(&registry_, 1.0);
          contexts::game_states::IncrementScore(&registry_, 1);
          break;
        case SDLK_d:
          entities::dino::SetDead(&registry_, res_manager_, true);
          score = contexts::game_states::GetScore(&registry_).value;
          high_score = contexts::game_states::GetHighscore(&registry_).value;
          high_score = score > high_score ? score : high_score;
          contexts::game_states::SetHighscore(&registry_, high_score);
          break;
        case SDLK_r:
          entities::dino::SetDead(&registry_, res_manager_, false);
          contexts::game_states::SetSpeed(&registry_, 1.0);
          contexts::game_states::SetScore(&registry_, 0);
          break;
        case SDLK_n:
          contexts::game_states::ToggleDark(&registry_);
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
        entities::dino::SetDead(&registry_, res_manager_, false);
        contexts::game_states::SetScore(&registry_, 0);
        contexts::game_states::SetSpeed(&registry_, 1.0);
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
  hud_.Update(&registry_);
}

void Game::Render() {
  auto color = colors::kBackgroundLight;
  if (contexts::game_states::GetDark(&registry_)) {
    color = colors::kBackgroundDark;
  }
  window_.Clear(color);

  systems::render::Sprites(window_.renderer(), &registry_);
  hud_.Draw(&registry_);
  window_.Present();
}

void Game::Run() {
  constexpr double kMSPerUpdate {1000.0 / kUpdatesPerSecond_};
  double previous_time = SDL_GetTicks();
  double lag = 0.0;
  uint32_t fps;
  uint32_t frames = 0;
  double frame_time_elapsed = 0.0;

  while (!contexts::game_states::GetOver(&registry_)) {
    const double kCurrentTime = SDL_GetTicks();
    const double kElapsed = kCurrentTime - previous_time;
    previous_time = kCurrentTime;
    lag += kElapsed;
    frame_time_elapsed += kElapsed;

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
    if (frame_time_elapsed > 250.0) {
      fps = frames / (frame_time_elapsed / 1000);
      contexts::graphics::SetFPS(&registry_, fps);
      frames = 0;
      frame_time_elapsed = 0.0;
    }
  }
}
