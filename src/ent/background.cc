/**
 * @file      background.cc
 * @brief     Background entity
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-09
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#include "ent/background.h"

#include <SDL2/SDL_rect.h>

#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>

#include "comp/sprite.h"
#include "comp/transform.h"
#include "core/graphics.h"
#include "core/vec2d.h"

struct SDL_Renderer;

namespace {

SDL_Rect position{0, 212, 400, 32};
vf2d direction{0.0, 0.0};

const char path[] = "res/image.png";
SDL_Rect clip{0, 0, 400, 32};

}  // namespace

namespace entities {

void CreateBackground(entt::registry* registry, SDL_Renderer* renderer) {
  const entt::entity e = registry->create();
  registry->emplace<components::Transform>(e, &position, direction);
  registry->emplace<components::Sprite>(
      e, graphics::LoadTexture(path, renderer), &clip);
}

}  // namespace entities
