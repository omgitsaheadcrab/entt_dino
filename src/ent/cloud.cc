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

#include <vector>

#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>

#include "comp/rigid_body.h"
#include "comp/sprite.h"
#include "comp/transform.h"
#include "core/res_manager.h"
#include "core/vec2d.h"
#include "util/random.h"

namespace {

// Rigid Body
vf2d velocity {-1.0, 0.0};
const vf2d acceleration {0.0, 0.0};

// Transform
const int initial_y_pos = 30;
SDL_Rect position {0, 0, 0, 0};

}  // namespace

namespace entities {

entt::entity CreateCloud(entt::registry* registry,
                         const ResourceManager& res_manager, const int xpos) {
  auto clips = res_manager.GetSpriteClips("cloud");
  position.x = xpos;
  position.y = initial_y_pos * utils::UniformRandom(1, 3);
  position.h = clips[0].h;
  position.w = clips[0].w;

  auto e = registry->create();
  registry->emplace<components::RigidBody>(e, velocity, acceleration);
  registry->emplace<components::Transform>(e, position);
  registry->emplace<components::Sprite>(
      e, res_manager.sprite_textures.find("cloud")->second, clips[0]);
  SPDLOG_DEBUG("{} was created", static_cast<int>(e));
  return e;
}

}  // namespace entities
