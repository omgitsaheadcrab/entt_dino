/**
 * @file      manage.cc
 * @brief     Entity state system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-04
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#include "sys/manage.h"

#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>

#include "comp/state.h"

void systems::manage::SetEntityState(entt::registry* registry,
                                     const entt::entity& entity,
                                     components::State* new_state) {
  registry->patch<components::State>(
      entity, [&](auto& state) { state.dead = new_state->dead; });
}

components::State systems::manage::GetEntityState(entt::registry* registry,
                                                  const entt::entity& entity) {
  auto& state = registry->get<components::State>(entity);
  return state;
}
