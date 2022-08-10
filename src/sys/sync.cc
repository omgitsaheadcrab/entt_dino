/**
 * @file      sync.cc
 * @brief     Synchronize graphics with physics
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-10
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#include "sys/sync.h"

#include <entt/entity/registry.hpp>

#include "comp/graphics/transform.h"
#include "comp/physics/transform.h"

void systems::sync::Transforms(entt::registry* registry) {
  const auto view = registry->view<components::graphics::Transform,
                                   components::physics::Transform>();
  view.each([&](auto& gfx, const auto& physx) {
    gfx.position.x = physx.position.x;
    gfx.position.y = physx.position.y;
    gfx.position.w = physx.position.w;
    gfx.position.h = physx.position.h;
  });
}
