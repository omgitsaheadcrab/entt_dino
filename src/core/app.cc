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
#include <string>

#include "core/game.h"

Application::Application(const std::string& kName, const int kScreen_width,
                         const int kScreen_height, const double kFps)
    : kScreen_width_ {kScreen_width},
      k_Screen_height_ {kScreen_height},
      kFps_ {kFps},
      kFrame_Delay_ {1000.0 / kFps},
      window_ {SDL_CreateWindow(kName.c_str(), SDL_WINDOWPOS_CENTERED,
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
  double previous_time = SDL_GetTicks();
  double lag = 0.0;

  Game game;
  game.Init(renderer_, kScreen_width_, k_Screen_height_);

  while (!game.is_over()) {
    double current_time = SDL_GetTicks();
    double elapsed = current_time - previous_time;
    previous_time = current_time;
    lag += elapsed;

    game.HandleEvents();

    while (lag >= kFrame_Delay_) {
      game.Update(renderer_);
      lag -= kFrame_Delay_;
    }

    game.Render(renderer_);
  }
  std::cout << "Veni. Vidi. Reverti.\n";
}
