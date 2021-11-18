/**
 * @file      app.cc
 * @brief     Main application handling SDL window creation.
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-05-27
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#include "core/app.h"

#include <SDL2/SDL.h>

#include <iostream>
#include <stdexcept>

#include "core/game.h"

Application::Application(const char* kName, const int kScreen_width,
                         const int kScreen_height, const double kFps)
    : kName_ {kName},
      kScreen_width_ {kScreen_width},
      k_Screen_height_ {kScreen_height},
      kFps_ {kFps},
      kFrame_Delay_ {1000.0 / kFps},
      window_ {SDL_CreateWindow(kName, SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, kScreen_width,
                                kScreen_height, SDL_WINDOW_RESIZABLE)},
      renderer_ {SDL_CreateRenderer(
          window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE)} {
  if (window_ == nullptr) {
    throw std::runtime_error("`SDL_CreateWindow` failed to create window.");
  }
  if (renderer_ == nullptr) {
    throw std::runtime_error("`SDL_CreateRenderer` failed to create renderer.");
  }
  SDL_RenderSetLogicalSize(renderer_, kScreen_width_, k_Screen_height_);
}

Application::~Application() {
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);
  SDL_Quit();
}

void Application::Run() {
  double frame_start;
  double frame_time;

  Game game;
  game.Init(renderer_);

  while (!game.is_over()) {
    frame_start = SDL_GetTicks();

    game.HandleEvents();
    game.Update(renderer_);
    game.Render(renderer_);

    frame_time = SDL_GetTicks() - frame_start;
    if (kFrame_Delay_ > frame_time) {
      SDL_Delay(kFrame_Delay_ - frame_time);
    }
  }
  std::cout << "Veni. Vidi. Reverti.\n";
}
