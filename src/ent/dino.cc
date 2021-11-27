/**
 * @file      dino.cc
 * @brief     Dino entity
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-11-25
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#include "ent/dino.h"

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

#include <iostream>
#include <string>

#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>

#include "comp/rigid_body.h"
#include "comp/sprite.h"
#include "comp/transform.h"
#include "core/graphics.h"
#include "core/vec2d.h"
#include "util/res.h"

namespace {

// Rigid Body
vf2d velocity {0.0, 0.0};
const vf2d acceleration {0.0, 0.0};

// Sprite
const std::string path {utils::GetResPath("dino.png")};
SDL_Rect clip {0, 0, 42, 44};

// Transform
SDL_Rect position {0, 0, 42, 44};

}  // namespace

namespace entities {

entt::entity CreateDino(entt::registry* registry, SDL_Renderer* renderer,
                        SDL_Rect* bounds) {
  position.x = bounds->w * 0.05;
  position.y = bounds->h * 0.77;
  const entt::entity e = registry->create();
  registry->emplace<components::RigidBody>(e, velocity, acceleration);
  registry->emplace<components::Sprite>(
      e, graphics::LoadTexture(path.c_str(), renderer), clip);
  registry->emplace<components::Transform>(e, position);
  std::cout << int(e) << " was created\n";
  return e;
}

}  // namespace entities
