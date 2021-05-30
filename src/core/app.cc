/**
 * @file      app.cc
 * @brief     Main application handling SDL window creation.
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-05-27
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#include "src/core/app.h"

#include <stdexcept>

const int Application::screen_width{800};
const int Application::screen_height{244};

Application::Application()
    : window{SDL_CreateWindow("entt-dino", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, screen_width,
                              screen_height, SDL_WINDOW_RESIZABLE)},
      renderer{SDL_CreateRenderer(
          window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE)} {
  if (window == nullptr) {
    throw std::runtime_error("`SDL_CreateWindow` failed to create window.");
  }
  if (renderer == nullptr) {
    throw std::runtime_error("`SDL_CreateRenderer` failed to create renderer.");
  }
  SDL_RenderSetLogicalSize(renderer, screen_width, screen_height);
}

Application::~Application() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
