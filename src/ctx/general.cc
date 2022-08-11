/**
 * @file      general.cc
 * @brief     General contexts
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-11
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#include "ctx/general.h"

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_video.h>

#include <cstdint>

#include <entt/entity/registry.hpp>

#include "comp/graphics/fps.h"
#include "comp/graphics/window_info.h"

components::graphics::WindowInfo contexts::GetWindowInfo(
    const entt::registry* registry) {
  return registry->ctx().get<components::graphics::WindowInfo>();
}

void contexts::SetWindowInfo(entt::registry* registry, SDL_Window* window) {
  int w, h;
  SDL_GetWindowSize(window, &w, &h);
  registry->ctx().insert_or_assign(
      components::graphics::WindowInfo {SDL_Rect {0, 0, w, h}});
}

components::graphics::FPS contexts::GetFPS(const entt::registry* registry) {
  return registry->ctx().get<components::graphics::FPS>();
}

void contexts::SetFPS(entt::registry* registry, const uint32_t fps) {
  registry->ctx().insert_or_assign(components::graphics::FPS {fps});
}
