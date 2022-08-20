/**
 * @file      floor.cc
 * @brief     Floor entity
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-09
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#include "ent/floor.h"

#include <SDL2/SDL_rect.h>
#include <spdlog/spdlog.h>

#include <entt/entity/registry.hpp>

#include "comp/entities/floor.h"
#include "comp/graphics/sprite.h"
#include "comp/graphics/transform.h"
#include "comp/physics/rigid_body.h"
#include "comp/physics/transform.h"
#include "core/vec2d.h"
#include "util/random.h"

namespace {

// Rigid Body
const vf2d kVelocity {-2.0, 0.0};
const vf2d kAcceleration {0.0, 0.0};

// Transform
SDL_Rect position {0, 212, 0, 0};

}  // namespace

void entities::background::CreateFloor(entt::registry* registry,
                                       const ResourceManager& kResManager,
                                       const int kXPos) {
  const auto kClips = kResManager.GetSpriteClips("floor");
  const auto kClip = utils::UniformRandom(0, 2);
  position.x = kXPos;
  position.h = kClips[kClip].h;
  position.w = kClips[kClip].w;

  auto e = registry->create();
  registry->emplace<components::entities::Floor>(e);
  registry->emplace<components::physics::RigidBody>(e, kVelocity,
                                                    kAcceleration);
  registry->emplace<components::graphics::Transform>(e, position);
  registry->emplace<components::physics::Transform>(e, position);
  registry->emplace<components::graphics::Sprite>(
      e, kResManager.GetSpriteTexture("floor"), kClips[kClip]);
  SPDLOG_DEBUG("{} was created", static_cast<int>(e));
}
