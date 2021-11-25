/**
 * @file      movement.cc
 * @brief     Movement system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-24
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#include "sys/movement.h"

#include <entt/entity/registry.hpp>

#include "comp/rigid_body.h"
#include "comp/transform.h"

void systems::Move(entt::registry* registry, unsigned int base_speed) {
  const auto view =
      registry->view<components::Transform, components::RigidBody>();
  view.each([&](auto& transform, const auto& rigid_body) {
    transform.position.x += rigid_body.velocity.x*base_speed;
  });
}
