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
#include <spdlog/spdlog.h>

SDL_Texture* graphics::LoadTexture(const char path[], SDL_Renderer* renderer) {
  SDL_Texture* texture = nullptr;
  SDL_Surface* loaded_surface = IMG_Load(path);

  if (loaded_surface == nullptr) {
    SPDLOG_ERROR("Unable to load image {}! SDL_image Error: ", path,
                 IMG_GetError());
  } else {
    texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
    if (texture == nullptr) {
      SPDLOG_ERROR("Unable to create texture from {}! SDL_image Error: ", path,
                   IMG_GetError());
    }
    SDL_FreeSurface(loaded_surface);
  }
  return texture;
}
