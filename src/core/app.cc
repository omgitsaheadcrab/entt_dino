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

Application::Application(const char* name, const int screen_width,
                         const int screen_height, const double fps)
    : name_{name},
      screen_width_{screen_width},
      screen_height_{screen_height},
      fps_{fps},
      frame_delay_{1000.0 / fps},
      window_{SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED, screen_width,
                               screen_height, SDL_WINDOW_RESIZABLE)},
      renderer_{SDL_CreateRenderer(
          window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE)} {
  if (window_ == nullptr) {
    throw std::runtime_error("`SDL_CreateWindow` failed to create window.");
  }
  if (renderer_ == nullptr) {
    throw std::runtime_error("`SDL_CreateRenderer` failed to create renderer.");
  }
  SDL_RenderSetLogicalSize(renderer_, screen_width_, screen_height_);
}

Application::~Application() {
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);
  SDL_Quit();
}

void Application::run() {
  std::cout << "Veni. Vidi. Reverti.\n";
}
