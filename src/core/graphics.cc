/**
 * @file      graphics.cc
 * @brief     Graphics utility functions
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-09
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#include "core/graphics.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>

namespace graphics {

SDL_Texture* LoadTexture(const char path[], SDL_Renderer* renderer) {
  SDL_Texture* texture = nullptr;
  SDL_Surface* loaded_surface = IMG_Load(path);

  if (loaded_surface == nullptr) {
    std::cout << "Unable to load image " << path
              << "! SDL_image Error: " << IMG_GetError() << "\n";
  } else {
    texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
    if (texture == nullptr) {
      std::cout << "Unable to create texture from " << path
                << "! SDL_image Error: " << SDL_GetError() << "\n";
    }
    SDL_FreeSurface(loaded_surface);
  }
  return texture;
}

}  // namespace graphics
