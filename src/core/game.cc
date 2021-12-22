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

#include "core/window.h"
#include "ent/dino.h"
#include "sys/background.h"
#include "sys/despawn.h"
#include "sys/movement.h"
#include "sys/render.h"

Game::Game(const int kWindowWidth, const int kWindowHeight)
    : window_ {"entt_dino", kWindowWidth, kWindowHeight},
      bounds_ {0, 0, kWindowWidth, kWindowHeight} {
  Init();
}

void Game::Init() {
  over_ = false;
  base_speed_ = 1;
  entities::CreateDino(&registry_, window_.renderer(), bounds_);
  systems::SpawnBackgroundElements(&registry_, window_.renderer(),
                                   &cloud_entities_, &floor_entities_, bounds_);
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
          break;
      }
      break;
    default:
      break;
  }
}

void Game::Update() {
  systems::Move(&registry_, base_speed_);
  std::set<entt::entity> del = systems::Despawn(&registry_);
  for (auto& e : del) {
    floor_entities_.erase(e);
    cloud_entities_.erase(e);
  }
  systems::SpawnBackgroundElements(&registry_, window_.renderer(),
                                   &cloud_entities_, &floor_entities_, bounds_);
}

void Game::Render() {
  SDL_SetRenderDrawColor(window_.renderer(), 239, 239, 239, 255);
  SDL_RenderClear(window_.renderer());
  systems::RenderSprites(window_.renderer(), &registry_);
  SDL_RenderPresent(window_.renderer());
}

void Game::Run() {
  const double kMSPerUpdate {1000.0 / kUpdatesPerSecond_};
  double previous_time = SDL_GetTicks();
  double lag = 0.0;
  int frames = 0;
  double frames_elapsed = 0.0;
  double fps = 0.0;

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
      frames = 0;
      frames_elapsed = 0.0;
    }
  }
}
