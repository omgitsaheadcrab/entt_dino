/**
 * @file      dead.cc
 * @brief     Dead state
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-09-14
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#include "states/dead.h"

#include "comp/graphics/sprite.h"
#include "comp/graphics/transform.h"
#include "comp/identifiers/dino.h"
#include "comp/physics/rigid_body.h"
#include "core/game.h"
#include "ctx/game_states.h"

void states::Dead::Set() {
  const auto& kClips =
      game_->res_manager().GetSpriteClipsFromSlices("dino", name_);
  const auto& kView = registry_->view<
      components::identifiers::Dino, components::graphics::Sprite,
      components::graphics::Transform, components::physics::RigidBody>();

  kView.each([&](auto& sprite, auto& transform, auto& rigid_body) {
    sprite.clip = kClips.front();
    transform.position.w = sprite.clip.w;
    transform.position.h = sprite.clip.h;
    rigid_body.velocity.y = 0;
    rigid_body.acceleration.y = 0;
  });
}
