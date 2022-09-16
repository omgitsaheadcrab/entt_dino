/**
 * @file      dead.cc
 * @brief     Dead state
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-09-14
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#include "states/dead.h"

#include "comp/entity/states.h"
#include "comp/graphics/sprite.h"
#include "comp/identifiers/dino.h"
#include "core/game.h"

void states::Dead::Set() {
  const auto& kClips = game_->res_manager().GetSpriteClips("dino", "dead");
  const auto& kView =
      registry_->view<components::identifiers::Dino, components::entity::State,
                      components::graphics::Sprite>();

  kView.each([&](auto& state, auto& sprite) {
    state.current = type_;
    sprite.clip = kClips.front();
  });
}
