/**
 * @file      graphics.cc
 * @brief     Graphics contexts
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2025-08-11
 * @copyright Copyright © 2025 Tobias Backer Dirks
 */

#include "ctx/graphics.h"

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_video.h>

#include <entt/entity/registry.hpp>

#include "comp/graphics/bounds.h"

void contexts::graphics::SetBounds(entt::registry* registry,
                                   SDL_Window* window) {
  int w, h;
  SDL_GetWindowSize(window, &w, &h);
  registry->ctx().insert_or_assign(
      components::graphics::Bounds {SDL_Rect {0, 0, w, h}});
}
