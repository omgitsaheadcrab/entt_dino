/**
 * @file      jumping.cc
 * @brief     Jumping state state
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-09-14
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#include "states/jumping.h"

#include "comp/entity/states.h"
#include "comp/graphics/sprite.h"
#include "comp/identifiers/dino.h"
#include "comp/physics/rigid_body.h"
#include "core/game.h"

void states::Jumping::Set() {
  const auto& kClips = game_->res_manager().GetSpriteClips("dino", "jumping");
  const auto& kView =
      registry_->view<components::identifiers::Dino, components::entity::State,
                      components::graphics::Sprite,
                      components::physics::RigidBody>();

  kView.each([&](auto& state, auto& sprite, auto& rigid_body) {
    state.current = type_;
    sprite.clip = kClips.front();
  });
}
