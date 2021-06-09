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

void CreateBackground(entt::registry& registry, SDL_Renderer* renderer) {
  const entt::entity e = registry.create();
  registry.emplace<Transform>(e, vf2d{0.0, 0.0}, vf2d{0.0, 0.0},
                              vf2d{0.0, 0.0});
  registry.emplace<Sprite>(e, LoadTexture("res/image.png", renderer),
                           vf2d{0.0, 0.0}, vf2d{0.0, 0.0});
}
