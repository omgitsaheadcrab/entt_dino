/**
 * @file      running.cc
 * @brief     Running state system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-09-01
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#include "sys/states/running.h"

#include "comp/entities/dino.h"
#include "comp/entity_states/dead.h"
#include "comp/entity_states/running.h"
#include "comp/graphics/sprite.h"
#include "core/game.h"
#include "events/dino/running.h"

void systems::states::Running::OnInit() {
  dispatcher_->sink<events::dino::Running>()
      .connect<&systems::states::Running::OnRunning>(this);

  const auto& kView = registry_->view<components::entities::Dino>();
  kView.each([&](auto entity) {
    registry_->emplace_or_replace<components::entity_states::Running>(entity);
  });
}

void systems::states::Running::OnRunning(const events::dino::Running&) {
  const auto& kClips = game_->res_manager().GetSpriteClips("dino");
  const auto& kView =
      registry_
          ->view<components::entities::Dino, components::graphics::Sprite>();

  kView.each([&](auto entity, auto sprite) {
    // Remove all other states
    registry_->remove<components::entity_states::Dead>(entity);

    // Add running state and set sprite
    registry_->emplace_or_replace<components::entity_states::Running>(entity);
    registry_->patch<components::graphics::Sprite>(
        entity, [&](auto& sprite) { sprite.clip = kClips[2]; });
  });
}
