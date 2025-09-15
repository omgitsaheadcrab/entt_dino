/**
 * @file      floor.cc
 * @brief     Floor entity
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2025-09-15
 * @copyright Copyright © 2025 Tobias Backer Dirks
 */

#include "ent/floor.h"

#include <SDL2/SDL_rect.h>
#include <spdlog/spdlog.h>

#include <entt/entity/registry.hpp>

#include "comp/graphics/sprite.h"
#include "comp/graphics/transform.h"
#include "comp/identifiers/floor.h"
#include "comp/physics/collider.h"
#include "comp/physics/rigid_body.h"
#include "comp/physics/transform.h"
#include "core/vec2d.h"
#include "ctx/graphics.h"
#include "util/random.h"

namespace {

// Rigid Body
const vf2d kVelocity {-2.0, 0.0};
const vf2d kAcceleration {0.0, 0.0};

// Transform
SDL_Rect position {0, 0, 0, 0};

// Collider
SDL_Rect box {0, 0, 0, 0};

}  // namespace

void entities::background::CreateFloor(entt::registry* registry,
                                       const omg::ResourceManager& kResManager,
                                       const int kXPos) {
  const auto& kBounds = contexts::graphics::GetBounds(registry);
  const auto& kClips = kResManager.GetSpriteClips("floor", "floor");
  const auto kClip = utils::UniformRandom(0, kClips.size() - 1);
  position.x = kXPos;
  position.h = kClips[kClip].h;
  position.y = kBounds.position.h - position.h;
  position.w = kClips[kClip].w;

  box.h = position.h / 2;
  box.y = kClips[kClip].h / 2;
  box.w = position.w;

  auto e = registry->create();

  registry->emplace<components::identifiers::Floor>(e);
  registry->emplace<components::physics::RigidBody>(e, kVelocity,
                                                    kAcceleration);
  registry->emplace<components::graphics::Transform>(e, position);
  registry->emplace<components::physics::Transform>(e, position);
  registry->emplace<components::physics::Collider>(e, box);
  registry->emplace<components::graphics::Sprite>(
      e, kResManager.GetSpriteTexture("floor"), kClips[kClip]);
  SPDLOG_DEBUG("{} was created", static_cast<int>(e));
}
