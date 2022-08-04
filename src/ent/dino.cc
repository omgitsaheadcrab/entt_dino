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

#include <vector>

#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>

#include "comp/rigid_body.h"
#include "comp/sprite.h"
#include "comp/state.h"
#include "comp/transform.h"
#include "core/res_manager.h"
#include "core/vec2d.h"
#include "util/res.h"

namespace {

// Rigid Body
const vf2d velocity {0.0, 0.0};
const vf2d acceleration {0.0, 0.0};

// Transform
SDL_Rect position {0, 0, 0, 0};

// State
const bool dead = false;
const bool jumping = false;

}  // namespace

namespace entities {

entt::entity CreateDino(entt::registry* registry,
                        const ResourceManager& res_manager,
                        const SDL_Rect& bounds) {
  auto clips = res_manager.GetSpriteClips("dino");
  position.x = bounds.w * 0.05;
  position.y = bounds.h * 0.77;
  position.h = clips[0].h;
  position.w = clips[0].w;

  auto e = registry->create();
  registry->emplace<components::RigidBody>(e, velocity, acceleration);
  registry->emplace<components::Transform>(e, position);
  registry->emplace<components::Sprite>(
      e, res_manager.sprite_textures.find("dino")->second, clips[0]);
  registry->emplace<components::State>(e, dead, jumping);
  SPDLOG_DEBUG("{} was created", static_cast<int>(e));
  return e;
}

}  // namespace entities
