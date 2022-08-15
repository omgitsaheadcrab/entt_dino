/**
 * @file      move.cc
 * @brief     Move system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-24
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#include "sys/move.h"

#include <entt/entity/registry.hpp>

#include "comp/physics/rigid_body.h"
#include "comp/physics/transform.h"
#include "ctx/game_states.h"

void systems::move::RigidBodies(entt::registry* registry) {
  const auto view = registry->view<components::physics::Transform,
                                   components::physics::RigidBody>();
  const auto base_speed = contexts::game_states::GetSpeed(registry);
  view.each([&](auto& transform, const auto& rigid_body) {
    transform.position.x += rigid_body.velocity.x * base_speed.value;
  });
}
