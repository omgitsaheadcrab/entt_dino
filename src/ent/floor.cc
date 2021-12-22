/**
 * @file      floor.cc
 * @brief     Floor entity
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-09
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#include "ent/floor.h"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <spdlog/spdlog.h>

#include <memory>

#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>

#include "comp/rigid_body.h"
#include "comp/sprite.h"
#include "comp/transform.h"
#include "core/graphics.h"
#include "core/vec2d.h"
#include "util/random.h"
#include "util/res.h"

namespace {

// Rigid Body
vf2d velocity {-2.0, 0.0};
const vf2d acceleration {0.0, 0.0};

// Sprite
static const std::shared_ptr<char[]> path {
    utils::GetResPath("sprites/floor.png")};
SDL_Rect clip {0, 0, 400, 32};

// Transform
SDL_Rect position {0, 212, 400, 32};

}  // namespace

namespace entities {

entt::entity CreateFloor(entt::registry* registry, SDL_Renderer* renderer,
                         const int xpos) {
  // TODO(omgitsaheadcrab): move all data out of floor factory
  clip.y = clip.h * utils::UniformRandom(0, 2);
  position.x = xpos;
  const entt::entity e = registry->create();
  registry->emplace<components::RigidBody>(e, velocity, acceleration);
  registry->emplace<components::Sprite>(
      e, graphics::LoadTexture(IMG_Load(path.get()), renderer), clip);
  registry->emplace<components::Transform>(e, position);
  SPDLOG_DEBUG("{} was created", static_cast<int>(e));
  return e;
}

}  // namespace entities
