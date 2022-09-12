/**
 * @file      despawn.cc
 * @brief     Despawn system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-11-18
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#include "sys/despawn.h"

#include <spdlog/spdlog.h>

#include "comp/entity_states/despawn.h"

void systems::Despawn::Update(const double dt) {
  auto view = registry_->view<components::entity_states::Despawn>();
#ifdef _DEBUG
  for (const auto& [entity] : view.each()) {
    SPDLOG_DEBUG("{} was deleted", static_cast<int>(entity));
  }
#endif  // _DEBUG
  registry_->destroy(view.begin(), view.end());
}
