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

#include <entt/entity/registry.hpp>

#include "comp/identifiers/dino.h"
#include "comp/entity_states/action.h"
#include "comp/graphics/sprite.h"
#include "comp/graphics/transform.h"
#include "comp/physics/rigid_body.h"
#include "comp/physics/transform.h"
#include "core/res_manager.h"
#include "core/vec2d.h"
#include "ctx/graphics.h"

namespace {

// Rigid Body
const vf2d kVelocity {0.0, 0.0};
const vf2d kAcceleration {0.0, 0.0};

// Transform
SDL_Rect position {0, 0, 0, 0};

}  // namespace

void entities::dino::Create(entt::registry* registry,
                            const omg::ResourceManager& kResManager) {
  const auto& kBounds = contexts::graphics::GetBounds(registry);
  const auto kClips = kResManager.GetSpriteClips("dino");
  const auto kClip = 1;
  position.x = kBounds.position.w * 0.05;
  position.y = kBounds.position.h * 0.77;
  position.h = kClips[kClip].h;
  position.w = kClips[kClip].w;

  auto e = registry->create();
  registry->emplace<components::identifiers::Dino>(e);
  registry->emplace<components::entity_states::Action>(e, Actions::running);
  registry->emplace<components::physics::RigidBody>(e, kVelocity,
                                                    kAcceleration);
  registry->emplace<components::graphics::Transform>(e, position);
  registry->emplace<components::physics::Transform>(e, position);
  registry->emplace<components::graphics::Sprite>(
      e, kResManager.GetSpriteTexture("dino"), kClips[kClip]);
  SPDLOG_DEBUG("{} was created", static_cast<int>(e));
}

bool entities::dino::IsCurrentAction(entt::registry* registry,
                                     const Actions kAction) {
  const auto kView = registry->view<components::identifiers::Dino,
                                    components::entity_states::Action>();
  bool is_current = false;
  kView.each([&](const auto& action) {
    if (action.current == Actions::dead) {
      is_current = true;
    }
  });
  return is_current;
}
