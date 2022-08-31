/**
 * @file      dead.cc
 * @brief     Dead state system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-09-01
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#include "sys/states/dead.h"

#include "comp/entities/dino.h"
#include "comp/entity_states/dead.h"
#include "comp/entity_states/running.h"
#include "comp/graphics/sprite.h"
#include "core/game.h"
#include "events/dino/dead.h"

void systems::states::Dead::OnInit() {
  dispatcher_->sink<events::dino::Dead>()
      .connect<&systems::states::Dead::OnDead>(this);
}

void systems::states::Dead::OnDead(const events::dino::Dead&) {
  const auto& kClips = game_->res_manager().GetSpriteClips("dino");
  const auto& kView =
      registry_
          ->view<components::entities::Dino, components::graphics::Sprite>();

  kView.each([&](auto entity, auto sprite) {
    // Remove all other states
    registry_->remove<components::entity_states::Running>(entity);

    // Add dead state and change sprite
    registry_->emplace_or_replace<components::entity_states::Dead>(entity);
    registry_->patch<components::graphics::Sprite>(
        entity, [&](auto& sprite) { sprite.clip = kClips[0]; });
  });
}
