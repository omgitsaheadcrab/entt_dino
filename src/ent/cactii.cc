/**
 * @file      cactii.cc
 * @brief     Cactii entity
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2025-11-25
 * @copyright Copyright © 2025 Tobias Backer Dirks
 */

#include "ent/cactii.h"

#include <SDL2/SDL_rect.h>
#include <spdlog/spdlog.h>

#include <entt/entity/registry.hpp>

#include "comp/graphics/sprite.h"
#include "comp/graphics/transform.h"
#include "comp/identifiers/enemy.h"
#include "comp/physics/collider.h"
#include "comp/physics/rigid_body.h"
#include "comp/physics/transform.h"
#include "core/res_manager.h"
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

void entities::enemies::CreateCactii(entt::registry* registry,
                                     const omg::ResourceManager& kResManager,
                                     const int kXPos) {
  const auto& kBounds = contexts::graphics::GetBounds(registry);
  const auto& kClips = kResManager.GetSpriteClipsFromSlices("cactii", "cactii");
  const auto& kFloorClips = kResManager.GetSpriteClips("floor", "floor");
  const auto kClip = utils::UniformRandom(0, kClips.size() - 1);

  position.x = kXPos;
  position.h = kClips[kClip].h;
  position.y = kBounds.position.h - kFloorClips.front().h / 2 - position.h;
  position.w = kClips[kClip].w;

  box.x = position.w / 8;
  box.h = position.h;
  box.w = 3 * position.w / 4;

  auto e = registry->create();

  registry->emplace<components::identifiers::Enemy>(e);
  registry->emplace<components::physics::RigidBody>(e, kVelocity,
                                                    kAcceleration);
  registry->emplace<components::graphics::Transform>(e, position);
  registry->emplace<components::physics::Transform>(e, position);
  registry->emplace<components::physics::Collider>(e, box);
  registry->emplace<components::graphics::Sprite>(
      e, kResManager.GetSpriteTexture("cactii"), kClips[kClip]);
  SPDLOG_DEBUG("{} was created", static_cast<int>(e));
}
