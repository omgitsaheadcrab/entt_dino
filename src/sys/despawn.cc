/**
 * @file      despawn.cc
 * @brief     Despawn system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-11-18
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#include "sys/despawn.h"

#include <iostream>
#include <set>
#include <string>

#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>

#include "comp/transform.h"

std::set<entt::entity> systems::Despawn(entt::registry* registry) {
  std::set<entt::entity> deleted;
  const auto view = registry->view<components::Transform>();
  for (auto [entity, transform] : view.each()) {
    if (transform.position.x <= -transform.position.w) {
      std::cout << int(entity) << " was deleted\n";
      deleted.emplace(entity);
      registry->destroy(entity);
    }
  }
  return deleted;
}
