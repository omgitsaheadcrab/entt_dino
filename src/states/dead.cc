/**
 * @file      dead.cc
 * @brief     Dead state
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-09-14
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#include "states/dead.h"

#include "comp/graphics/sprite.h"
#include "comp/identifiers/dino.h"
#include "comp/physics/rigid_body.h"
#include "core/game.h"
#include "ctx/game_states.h"

void states::Dead::Set() {
  const auto& kClips = game_->res_manager().GetSpriteClips("dino", name_);
  const auto& kView =
      registry_
          ->view<components::identifiers::Dino, components::graphics::Sprite,
                 components::physics::RigidBody>();

  kView.each([&](auto& sprite, auto& rigid_body) {
    sprite.clip = kClips.front();
    rigid_body.velocity.y = 0;
    rigid_body.acceleration.y = 0;
  });
}
