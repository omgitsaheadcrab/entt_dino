/**
 * @file      cloud.cc
 * @brief     Cloud entity
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-11-25
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#include "ent/cloud.h"

#include <SDL2/SDL_rect.h>
#include <spdlog/spdlog.h>

#include <entt/entity/registry.hpp>

#include "comp/entities/cloud.h"
#include "comp/graphics/sprite.h"
#include "comp/graphics/transform.h"
#include "comp/physics/rigid_body.h"
#include "comp/physics/transform.h"
#include "core/res_manager.h"
#include "core/vec2d.h"
#include "util/random.h"

namespace {

// Rigid Body
const vf2d kVelocity {-1.0, 0.0};
const vf2d kAcceleration {0.0, 0.0};

// Transform
constexpr int kYPos = 30;
SDL_Rect position {0, 0, 0, 0};

}  // namespace

void entities::background::CreateCloud(entt::registry* registry,
                                       const ResourceManager& kResManager,
                                       const int kXPos) {
  const auto kClips = kResManager.GetSpriteClips("cloud");
  const auto kClip = 0;
  position.x = kXPos;
  position.y = kYPos * utils::UniformRandom(1, 3);
  position.h = kClips[kClip].h;
  position.w = kClips[kClip].w;

  auto e = registry->create();
  registry->emplace<components::entities::Cloud>(e);
  registry->emplace<components::physics::RigidBody>(e, kVelocity,
                                                    kAcceleration);
  registry->emplace<components::physics::Transform>(e, position);
  registry->emplace<components::graphics::Transform>(e, position);
  registry->emplace<components::graphics::Sprite>(
      e, kResManager.GetSpriteTexture("cloud"), kClips[kClip]);
  SPDLOG_DEBUG("{} was created", static_cast<int>(e));
}
