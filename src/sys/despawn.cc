/**
 * @file      despawn.cc
 * @brief     Despawn system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-11-18
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#include "sys/despawn.h"

#include <spdlog/spdlog.h>

#include <entt/entity/registry.hpp>

#include "comp/tags.h"

void systems::despawn::OutOfBounds(entt::registry* registry) {
  const auto view = registry->view<components::entity_states::Despawn>();
#ifdef _DEBUG
  for (const auto& [entity] : view.each()) {
    SPDLOG_DEBUG("{} was deleted", static_cast<int>(entity));
  }
#endif  // _DEBUG
  registry->destroy(view.begin(), view.end());
}
