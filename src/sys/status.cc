/**
 * @file      status.cc
 * @brief     Status system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-24
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#include "sys/status.h"

#include <cstdint>

#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>

#include "comp/state.h"

void systems::SetEntityStatus(entt::registry* registry,
                              const entt::entity& entity,
                              components::State& new_state) {
  registry->patch<components::State>(entity, [&](auto& state) {
    state.dead = new_state.dead;
  });
}

components::State systems::GetEntityStatus(entt::registry* registry,
                                           const entt::entity& entity) {
  auto& state = registry->get<components::State>(entity);
  return state;
}
