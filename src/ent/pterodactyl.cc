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
#include <entt/entity/registry.hpp>

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
const vf2d kVelocity {-2.5, 0.0}; // Slightly faster than cactii
const vf2d kAcceleration {0.0, 0.0};

}  // namespace

void entities::enemies::CreatePterodactyl(entt::registry* registry,
                                          const omg::ResourceManager& kResManager,
                                          int x, int y) {
  // Get both animation frames for the pterodactyl
  const auto& kClips = kResManager.GetSpriteClips("pterodactyl", "pterodactyl");
  if (kClips.size() < 2) {
    SPDLOG_ERROR("Pterodactyl sprite must have at least 2 frames for animation!");
    return;
  }

  // Pick a random frame to start with
  int frame = utils::UniformRandom(0, 1);

  SDL_Rect position;
  position.x = x;
  position.y = y;
  position.h = kClips[frame].h;
  position.w = kClips[frame].w;

  // Collider (simple box, can be improved)
  SDL_Rect box;
  box.x = position.x;
  box.y = position.y;
  box.w = position.w;
  box.h = position.h;

  auto e = registry->create();

  registry->emplace<components::identifiers::Enemy>(e);
  registry->emplace<components::physics::RigidBody>(e, kVelocity, kAcceleration);
  registry->emplace<components::graphics::Transform>(e, position);
  registry->emplace<components::physics::Transform>(e, position);
  registry->emplace<components::physics::Collider>(e, box);
  registry->emplace<components::graphics::Sprite>(
      e, kResManager.GetSpriteTexture("pterodactyl"), kClips[frame]);
  // Store animation state in registry context or as a component if you have one

  SPDLOG_DEBUG("Pterodactyl entity {} was created at ({}, {})", static_cast<int>(e), position.x, position.y);
}
