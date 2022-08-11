/**
 * @file      contexts.cc
 * @brief     Contexts
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-11
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#include "ctx/contexts.h"

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_video.h>

#include <entt/entity/registry.hpp>

#include "comp/graphics/window_info.h"

void contexts::SetWindowInfo(entt::registry* registry, SDL_Window* window) {
  int w, h;
  SDL_GetWindowSize(window, &w, &h);
  registry->ctx().insert_or_assign(
      components::graphics::WindowInfo {SDL_Rect {0, 0, w, h}});
}
