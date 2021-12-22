/**
 * @file      graphics.cc
 * @brief     Graphics utility functions
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-09
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#include "core/graphics.h"

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <spdlog/spdlog.h>

SDL_Texture* graphics::LoadTexture(SDL_Surface* surface,
                                   SDL_Renderer* renderer) {
  SDL_Texture* texture = nullptr;

  if (surface == nullptr) {
    SPDLOG_ERROR("Unable to load resource!");
  } else {
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr) {
      SPDLOG_ERROR("Unable to create texture");
    }
    SDL_FreeSurface(surface);
  }
  return texture;
}
