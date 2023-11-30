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

#include "comp/identifiers/dino.h"
#include "comp/identifiers/enemy.h"
#include "events/entity/despawn.h"
#include "events/game/restart.h"

void systems::Despawn::OnInit() {
  dispatcher_->sink<events::entity::Despawn>()
      .connect<&systems::Despawn::OnDespawn>(this);
  dispatcher_->sink<events::game::Restart>()
      .connect<&systems::Despawn::OnRestart>(this);
}

void systems::Despawn::OnDespawn(const events::entity::Despawn& despawn) {
  SPDLOG_DEBUG("{} was destroyed.", static_cast<int>(*despawn.entity));
  registry_->destroy(*despawn.entity);
}

void systems::Despawn::OnRestart() {
  const auto kDinoView = registry_->view<components::identifiers::Dino>();
  kDinoView.each([&](auto entity) {
    dispatcher_->trigger(events::entity::Despawn {&entity});
  });

  const auto kEnemyView = registry_->view<components::identifiers::Enemy>();
  kEnemyView.each([&](auto entity) {
    dispatcher_->trigger(events::entity::Despawn {&entity});
  });
}
