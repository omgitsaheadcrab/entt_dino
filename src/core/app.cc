/**
 * @file      app.cc
 * @brief     Main application handling SDL window creation.
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-05-27
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#include "core/app.h"

#include <stdexcept>

const int Application::screen_width_{800};
const int Application::screen_height_{244};

Application::Application()
    : window_{SDL_CreateWindow("entt-dino", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, screen_width_,
                              screen_height_, SDL_WINDOW_RESIZABLE)},
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
