/**
 * @file      running.cc
 * @brief     Running state state
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-09-14
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#include "states/running.h"

#include "comp/entity/states.h"
#include "comp/graphics/sprite.h"
#include "comp/identifiers/dino.h"
#include "core/game.h"

void states::Running::Set() {
  const auto& kClips = game_->res_manager().GetSpriteClips("dino");
  const auto& kView =
      registry_
          ->view<components::identifiers::Dino, components::graphics::Sprite>();

  kView.each([&](auto entity, auto sprite) {
    // Set running state and set sprite
    registry_->patch<components::entity::State>(
        entity, [&](auto& state) { state.current = type_; });
    registry_->patch<components::graphics::Sprite>(
        entity, [&](auto& sprite) { sprite.clip = kClips[1]; });
  });
}
