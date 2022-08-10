/**
 * @file      window.cc
 * @brief     Window state
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-10
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#include "ent/state/window.h"

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_video.h>

#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>

#include "comp/graphics/window.h"

void entities::CreateWindowState(entt::registry* registry, SDL_Window* window) {
  int w, h;
  auto e = registry->create();
  SDL_GetWindowSize(window, &w, &h);
  registry->emplace<components::graphics::Window>(e, SDL_Rect {0, 0, w, h});
}
