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

#include <vector>

#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>

#include "comp/rigid_body.h"
#include "comp/sprite.h"
#include "comp/transform.h"
#include "core/vec2d.h"
#include "util/random.h"

namespace {

// Rigid Body
vf2d velocity {-2.0, 0.0};
const vf2d acceleration {0.0, 0.0};

// Transform
SDL_Rect position {0, 212, 0, 0};

}  // namespace

namespace entities {

entt::entity CreateFloor(entt::registry* registry,
                         const ResourceManager& res_manager, const int xpos) {
  auto clips = res_manager.GetSpriteClips("floor");
  auto clip_number = utils::UniformRandom(0, 2);
  position.x = xpos;
  position.h = clips[clip_number].h;
  position.w = clips[clip_number].w;

  auto e = registry->create();
  registry->emplace<components::RigidBody>(e, velocity, acceleration);
  registry->emplace<components::Transform>(e, position);
  registry->emplace<components::Sprite>(
      e, res_manager.sprite_textures.find("floor")->second, clips[clip_number]);
  SPDLOG_DEBUG("{} was created", static_cast<int>(e));
  return e;
}

}  // namespace entities
