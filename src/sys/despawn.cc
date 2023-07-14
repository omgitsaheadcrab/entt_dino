/**
 * @file      despawn.cc
 * @brief     Despawn system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-11-18
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#include "sys/despawn.h"

#include <spdlog/spdlog.h>

#include <entt/entt.hpp>

#include "events/entity/despawn.h"

void systems::Despawn::OnInit() {
  dispatcher_->sink<events::entity::Despawn>()
      .connect<&systems::Despawn::OnDespawn>(this);
}

void systems::Despawn::OnDespawn(const events::entity::Despawn& despawn) {
  SPDLOG_DEBUG("{} was destroyed.", static_cast<int>(*despawn.entity));
  registry_->destroy(*despawn.entity);
}
