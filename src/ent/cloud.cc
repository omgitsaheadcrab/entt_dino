/**
 * @file      cloud.cc
 * @brief     Cloud entity
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-11-25
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#include "ent/cloud.h"

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <spdlog/spdlog.h>

#include <string>

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
vf2d velocity {-1.0, 0.0};
const vf2d acceleration {0.0, 0.0};

// Sprite
const std::string path {utils::GetResPath("cloud.png")};
SDL_Rect clip {0, 0, 64, 16};

// Transform
SDL_Rect position {0, 0, 64, 16};

}  // namespace

namespace entities {

entt::entity CreateCloud(entt::registry* registry, SDL_Renderer* renderer,
                         int xpos) {
  position.y = 30 * utils::UniformRandom(1, 3);
  position.x = xpos;
  const entt::entity e = registry->create();
  registry->emplace<components::RigidBody>(e, velocity, acceleration);
  registry->emplace<components::Sprite>(
      e, graphics::LoadTexture(path.c_str(), renderer), clip);
  registry->emplace<components::Transform>(e, position);
  SPDLOG_DEBUG("{} was created", static_cast<int>(e));
  return e;
}

}  // namespace entities
