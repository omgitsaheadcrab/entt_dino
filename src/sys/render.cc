/**
 * @file      render.cc
 * @brief     Render system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-13
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#include "sys/render.h"

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

#include <entt/entity/registry.hpp>

#include "comp/sprite.h"
#include "comp/transform.h"

void systems::Render(SDL_Renderer* renderer, entt::registry* registry) {
  const auto view = registry->view<components::Sprite, components::Transform>();
  view.each([&](const auto& sprite, const auto& transform) {
    SDL_RenderCopy(renderer, sprite.sheet, &sprite.clip, &transform.position);
  });
}
