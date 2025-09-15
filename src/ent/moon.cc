/**
 * @file      moon.cc
 * @brief     Moon entity
 * @author    Tobias Backer Dirks <omgitsaheadcrab@gmail.com>
 * @date      2025-09-15
 * @copyright Copyright © 2025 Tobias Backer Dirks
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
#include "util/random.h"

namespace entities {
namespace background {

void CreateMoon(entt::registry* registry,
                const omg::ResourceManager& kResManager, double x, double y) {
  // Moon moves slowly to the left (parallax effect)
  const vf2d kVelocity {-0.3, 0.0};  // slower than clouds
  const vf2d kAcceleration {0.0, 0.0};

  // Try slices first, fallback to frame tag
  auto kClips = kResManager.GetSpriteClipsFromSlices("moon", "moon");
  const auto kClip = utils::UniformRandom(0, kClips.size() - 1);

  SDL_Rect position;
  position.x = static_cast<int>(x);
  position.y = static_cast<int>(y);
  position.h = kClips[kClip].h;
  position.w = kClips[kClip].w;

  auto texture = kResManager.GetSpriteTexture("moon");

  auto e = registry->create();
  registry->emplace<components::identifiers::Moon>(e);
  registry->emplace<components::physics::RigidBody>(e, kVelocity,
                                                    kAcceleration);
  registry->emplace<components::physics::Transform>(e, position);
  registry->emplace<components::graphics::Transform>(e, position);
  registry->emplace<components::graphics::Sprite>(e, texture, kClips[kClip]);
  SPDLOG_DEBUG("Moon entity {} was created at ({}, {})", static_cast<int>(e),
               position.x, position.y);
}

}  // namespace background
}  // namespace entities
