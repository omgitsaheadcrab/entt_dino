/**
 * @file      background.cc
 * @brief     Background entity
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-09
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#include "ent/background.h"

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>

#include "comp/rigid_body.h"
#include "comp/sprite.h"
#include "comp/transform.h"
#include "core/graphics.h"
#include "core/random.h"
#include "core/vec2d.h"
#include "util/res.h"

namespace {

// Rigid Body
vf2d velocity{-1.0, 0.0};
const vf2d acceleration{0.0, 0.0};

// Sprite
const std::string path{utils::GetResPath() + "image.png"};
SDL_Rect clip{0, 0, 400, 32};

// Transform
SDL_Rect position{0, 212, 400, 32};

}  // namespace

namespace entities {

void CreateBackground(entt::registry* registry, SDL_Renderer* renderer,
                      int xpos) {
  clip.y = clip.h * utils::uniform_random(0, 2);
  position.x = xpos;
  const entt::entity e = registry->create();
  registry->emplace<components::RigidBody>(e, velocity, acceleration);
  registry->emplace<components::Sprite>(
      e, graphics::LoadTexture(path.c_str(), renderer), clip);
  registry->emplace<components::Transform>(e, position);
}

}  // namespace entities
