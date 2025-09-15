/**
 * @file      star.cc
 * @brief     Star entity
 * @author    Tobias Backer Dirks <omgitsaheadcrab@gmail.com>
 * @date      2025-06-10
 * @copyright Copyright © 2025 Tobias Backer Dirks
 */

#include "ent/star.h"

#include <SDL2/SDL_rect.h>
#include <spdlog/spdlog.h>

#include <vector>

#include <entt/entity/registry.hpp>

#include "comp/graphics/animation.h"
#include "comp/graphics/sprite.h"
#include "comp/graphics/transform.h"
#include "comp/identifiers/star.h"
#include "comp/physics/rigid_body.h"
#include "comp/physics/transform.h"
#include "core/res_manager.h"
#include "core/vec2d.h"
#include "util/random.h"

namespace entities {
namespace background {

void CreateStar(entt::registry* registry,
                const omg::ResourceManager& kResManager, double x, double y) {
  // Stars move very slowly to the left (parallax effect)
  const vf2d kVelocity {-0.15, 0.0};  // much slower than clouds
  const vf2d kAcceleration {0.0, 0.0};

  // Try slices first, fallback to frame tag
  auto kClips = kResManager.GetSpriteClipsFromSlices("star", "star");
  // Pick a random frame to start with
  const auto kClip = utils::UniformRandom(0, kClips.size() - 1);

  SDL_Rect position;
  position.x = static_cast<int>(x);
  position.y = static_cast<int>(y);
  position.h = kClips[kClip].h;
  position.w = kClips[kClip].w;

  auto texture = kResManager.GetSpriteTexture("star");

  auto e = registry->create();
  registry->emplace<components::identifiers::Star>(e);
  registry->emplace<components::physics::RigidBody>(e, kVelocity,
                                                    kAcceleration);
  registry->emplace<components::physics::Transform>(e, position);
  registry->emplace<components::graphics::Transform>(e, position);
  registry->emplace<components::graphics::Sprite>(e, texture, kClips[kClip]);
  // Add animation component for star (slow cycle between frames)
  registry->emplace<components::graphics::Animation>(
      e,
      components::graphics::Animation(
          std::vector<SDL_Rect>(kClips.begin(), kClips.end()), kClip, 0, 600));
  SPDLOG_DEBUG("Star entity {} was created at ({}, {})", static_cast<int>(e),
               position.x, position.y);
}

}  // namespace background
}  // namespace entities
