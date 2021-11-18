/**
 * @file      despawn.cc
 * @brief     Despawn system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-11-18
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#include "sys/despawn.h"

#include <entt/entity/registry.hpp>

#include "comp/transform.h"

void systems::Despawn(entt::registry* registry) {
  const auto view = registry->view<components::Transform>();
  for (auto [entity, transform] : view.each()) {
    if (transform.position.x <= -transform.position.w) {
      registry->destroy(entity);
    }
  }
}
