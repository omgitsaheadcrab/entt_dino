/**
 * @file      dino.cc
 * @brief     Dino entity
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-11-25
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#include "ent/dino.h"

#include <SDL2/SDL_rect.h>
#include <spdlog/spdlog.h>

#include <entt/entity/registry.hpp>

#include "comp/graphics/sprite.h"
#include "comp/graphics/transform.h"
#include "comp/graphics/animation.h"
#include "comp/identifiers/dino.h"
#include "comp/physics/collider.h"
#include "comp/physics/rigid_body.h"
#include "comp/physics/transform.h"
#include "core/res_manager.h"
#include "core/vec2d.h"
#include "ctx/graphics.h"

namespace {

// Rigid Body
const vf2d kVelocity {0.0, 0.0};
const vf2d kAcceleration {0.0, 0.0};

// Transform
SDL_Rect position {0, 0, 0, 0};

// Collider
SDL_Rect box {0, 0, 0, 0};

}  // namespace

void entities::dino::Create(entt::registry* registry,
                            const omg::ResourceManager& kResManager) {
  const auto& kBounds = contexts::graphics::GetBounds(registry);
  const auto& kClips = kResManager.GetSpriteClipsFromSlices("dino", "running");
  const auto& kFloorClips = kResManager.GetSpriteClips("floor", "floor");

  position.x = kBounds.position.w * 0.05;
  position.h = kClips.front().h;
  position.y = kBounds.position.h - kFloorClips.front().h / 2 - position.h;
  position.w = kClips.front().w;

  box.x = kClips.front().w / 8;
  box.h = position.h;
  box.w = 3 * position.w / 4;

  auto e = registry->create();
  registry->emplace<components::identifiers::Dino>(e);
  registry->emplace<components::physics::RigidBody>(e, kVelocity,
                                                    kAcceleration);
  registry->emplace<components::graphics::Transform>(e, position);
  registry->emplace<components::physics::Transform>(e, position);
  registry->emplace<components::physics::Collider>(e, box);
  registry->emplace<components::graphics::Sprite>(
      e, kResManager.GetSpriteTexture("dino"), kClips.front());
  registry->emplace<components::graphics::Animation>(
      e,
      components::graphics::Animation(
          std::vector<SDL_Rect>(kClips.begin(), kClips.end()), 0, 0, 120));
  SPDLOG_DEBUG("{} was created", static_cast<int>(e));
}
