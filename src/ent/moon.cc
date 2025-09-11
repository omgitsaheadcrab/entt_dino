/**
 * @file      moon.cc
 * @brief     Moon entity
 * @author    Tobias Backer Dirks <omgitsaheadcrab@gmail.com>
 * @date      2024-06-10
 * @copyright Copyright © 2024 Tobias Backer Dirks
 */

#include "ent/moon.h"

#include <SDL2/SDL_rect.h>
#include <spdlog/spdlog.h>

#include <entt/entity/registry.hpp>

#include "comp/graphics/sprite.h"
#include "comp/graphics/transform.h"
#include "comp/identifiers/moon.h"
#include "comp/physics/rigid_body.h"
#include "comp/physics/transform.h"
#include "core/res_manager.h"
#include "core/vec2d.h"

namespace {

// Moon doesn't move, so velocity and acceleration are zero
const vf2d kVelocity {0.0, 0.0};
const vf2d kAcceleration {0.0, 0.0};

}  // namespace

void entities::background::CreateMoon(entt::registry* registry,
                                      const omg::ResourceManager& kResManager,
                                      double x, double y) {
  const auto& kClips = kResManager.GetSpriteClips("moon", "moon");
  SDL_Rect position;
  position.x = static_cast<int>(x);
  position.y = static_cast<int>(y);
  position.h = kClips.empty() ? 32 : kClips.front().h;
  position.w = kClips.empty() ? 32 : kClips.front().w;

  auto e = registry->create();
  registry->emplace<components::identifiers::Moon>(e);
  registry->emplace<components::physics::RigidBody>(e, kVelocity, kAcceleration);
  registry->emplace<components::physics::Transform>(e, position);
  registry->emplace<components::graphics::Transform>(e, position);
  if (!kClips.empty()) {
    registry->emplace<components::graphics::Sprite>(
        e, kResManager.GetSpriteTexture("moon"), kClips.front());
  }
  SPDLOG_DEBUG("Moon entity {} was created", static_cast<int>(e));
}
