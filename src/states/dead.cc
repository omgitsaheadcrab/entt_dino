/**
 * @file      dead.cc
 * @brief     Dead state
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-09-14
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#include "states/dead.h"

#include "comp/graphics/animation.h"
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
      components::graphics::Transform, components::physics::RigidBody,
      components::graphics::Animation>();

  kView.each(
      [&](auto& sprite, auto& transform, auto& rigid_body, auto& animation) {
        // For dead, use only the first frame (not animated)
        animation.frames = {kClips.front()};
        animation.current_frame = 0;
        animation.elapsed = 0;
        animation.frame_duration = 1000;  // Large value, disables animation

        sprite.clip = animation.frames[animation.current_frame];
        transform.position.w = sprite.clip.w;
        transform.position.h = sprite.clip.h;
        rigid_body.velocity.y = 0;
        rigid_body.acceleration.y = 0;
      });
  Mix_PlayChannel(-1, game_->res_manager().GetSound("dead"), 0);
}
