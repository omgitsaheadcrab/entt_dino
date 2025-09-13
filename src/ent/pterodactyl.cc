/**
 * @file      pterodactyl.cc
 * @brief     Pterodactyl entity
 * @author    Tobias Backer Dirks <omgitsaheadcrab@gmail.com>
 * @date      2024-06-11
 * @copyright Copyright © 2024 Tobias Backer Dirks
 */

#include "ent/pterodactyl.h"

#include <SDL2/SDL_rect.h>
#include <spdlog/spdlog.h>

#include <vector>

#include <entt/entity/registry.hpp>

#include "comp/graphics/animation.h"
#include "comp/graphics/sprite.h"
#include "comp/graphics/transform.h"
#include "comp/identifiers/enemy.h"
#include "comp/physics/collider.h"
#include "comp/physics/rigid_body.h"
#include "comp/physics/transform.h"
#include "core/res_manager.h"
#include "core/vec2d.h"
#include "util/random.h"

namespace {

// Rigid Body
const vf2d kVelocity {-2.2, 0.0};  // Slightly faster than cactii
const vf2d kAcceleration {0.0, 0.0};

}  // namespace

void entities::enemies::CreatePterodactyl(
    entt::registry* registry, const omg::ResourceManager& kResManager, int x,
    int y) {
  // Get both animation frames for the pterodactyl
  const auto& kClips =
      kResManager.GetSpriteClipsFromSlices("pterodactyl", "pterodactyl");

  // Pick a random frame to start with
  const auto kClip = utils::UniformRandom(0, 1);

  SDL_Rect position;
  position.x = x;
  position.y = y;
  position.h = kClips[kClip].h;
  position.w = kClips[kClip].w;

  // Collider (simple box, can be improved)
  SDL_Rect box;
  box.x = position.w / 8;
  box.y = 0;
  box.w = 3 * position.w / 4;
  box.h = position.h;

  auto e = registry->create();

  registry->emplace<components::identifiers::Enemy>(e);
  registry->emplace<components::physics::RigidBody>(e, kVelocity,
                                                    kAcceleration);
  registry->emplace<components::graphics::Transform>(e, position);
  registry->emplace<components::physics::Transform>(e, position);
  registry->emplace<components::physics::Collider>(e, box);
  registry->emplace<components::graphics::Sprite>(
      e, kResManager.GetSpriteTexture("pterodactyl"), kClips[kClip]);
  // Add animation component using the new constructor
  registry->emplace<components::graphics::Animation>(
      e,
      components::graphics::Animation(
          std::vector<SDL_Rect>(kClips.begin(), kClips.end()), kClip, 0, 160));

  SPDLOG_DEBUG("Pterodactyl entity {} was created at ({}, {})",
               static_cast<int>(e), position.x, position.y);
}
