/**
 * @file      background.cc
 * @brief     Background entity
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-09
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#include "ent/background.h"

#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>

#include "comp/sprite.h"
#include "comp/transform.h"
#include "core/graphics.h"
#include "core/vec2d.h"

struct SDL_Renderer;

namespace {

vf2d position{0.0, 0.0};
vf2d direction{0.0, 0.0};
vf2d scale{0.0, 0.0};

vf2d sprite_position{0.0, 0.0};
vf2d sprite_size{0.0, 0.0};

const char path[] = "res/image.png";

}  // namespace

namespace entities {

void CreateBackground(entt::registry* registry, SDL_Renderer* renderer) {
  const entt::entity e = registry->create();
  registry->emplace<components::Transform>(e, position, direction, scale);
  registry->emplace<components::Sprite>(
      e, graphics::LoadTexture(path, renderer), sprite_position, sprite_size);
}

}  // namespace entities
