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
#include <SDL2/SDL_timer.h>

#include <memory>

#include "core/hud.h"
#include "core/res_manager.h"
#include "core/scene_manager.h"
#include "core/window.h"
#include "scenes/dinosaur.h"
#include "scenes/opening_credits.h"

omg::Game::Game(const int kWindowWidth, const int kWindowHeight)
    : over_ {false},
      fps_ {0},
      window_ {"entt_dino", kWindowWidth, kWindowHeight},
      scene_manager_ {this} 
{
  // Ensure resources are loaded before any scene is initialized
  res_manager_.Init(window_.renderer());
}

omg::HUD& omg::Game::hud() { return hud_; }

uint32_t omg::Game::fps() { return fps_; }

omg::ResourceManager& omg::Game::res_manager() { return res_manager_; }

omg::SceneManager& omg::Game::scene_manager() { return scene_manager_; }

omg::Window& omg::Game::window() { return window_; }

void omg::Game::Run() {
  constexpr double kMSPerUpdate {1000.0 / kUpdatesPerSecond_};
  double previous_time = SDL_GetTicks();  // Casting to double
  double accumulator = 0.0;
  uint32_t frame_count_ = 0;
  double fps_interval_ = 0.0;

  scene_manager_.AddScene(std::make_unique<scenes::Dinosaur>());
  scene_manager_.AddScene(std::make_unique<scenes::OpeningCredits>());
  scene_manager_.SetCurrentScene("opening_credits");

  while (!over_) {
    const double kCurrentTime = SDL_GetTicks();  // Casting to double
    const double kFrameTime = kCurrentTime - previous_time;
    previous_time = kCurrentTime;
    accumulator += kFrameTime;

    auto scene = scene_manager_.current_scene();

    // HandleEvents as often as possible
    scene->HandleEvents();

    // Update only once per kMSPerUpdate
    while (accumulator >= kMSPerUpdate) {
      scene->Update(kMSPerUpdate);
      accumulator -= kMSPerUpdate;
    }

    // Render as often as possible
    scene->Render(kFrameTime);

    fps_interval_ += kFrameTime;
    frame_count_++;

    // Frame rate counter (updates every 250ms)
    if (fps_interval_ > 250.0) {
      fps_ = frame_count_ / (fps_interval_ / 1000);
      frame_count_ = 0;
      fps_interval_ = 0.0;
    }
  }
}

void omg::Game::Quit() { over_ = true; }
