/**
 * @file      move.cc
 * @brief     Move system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-24
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#include "sys/move.h"

#include <cmath>

#include <entt/entity/registry.hpp>

#include "comp/entities/dino.h"
#include "comp/entity_states/dead.h"
#include "comp/physics/rigid_body.h"
#include "comp/physics/transform.h"
#include "ctx/game_states.h"
#include "entt/core/type_traits.hpp"

void systems::move::RigidBodies(entt::registry* registry, const double dt) {
  const auto kView = registry->view<components::physics::Transform,
                                    components::physics::RigidBody>();
  const auto kDinoDead =
      registry
          ->view<components::entities::Dino, components::entity_states::Dead>();
  // Check if dino is dead, if he is do nothing
  if (kDinoDead.size_hint()) {
    return;
  }
  const auto kBaseSpeed = contexts::game_states::GetSpeed(registry);
  kView.each([&](auto& transform, const auto& kRigidBody) {
    // Need to round up to ensure sub pixel moves progress
    transform.position.x +=
        std::ceil(kRigidBody.velocity.x * dt * kBaseSpeed.value);
  });
}
