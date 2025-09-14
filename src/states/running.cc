/**
 * @file      running.cc
 * @brief     Running state state
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-09-14
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#include "states/running.h"

#include <cstdint>
#include <vector>

#include "comp/graphics/animation.h"
#include "comp/graphics/sprite.h"
#include "comp/graphics/transform.h"
#include "comp/identifiers/dino.h"
#include "comp/physics/collider.h"
#include "comp/physics/rigid_body.h"
#include "comp/physics/transform.h"
#include "core/game.h"
#include "ctx/game_states.h"
#include "ctx/graphics.h"

void states::Running::OnInit() {
  // No need to store animation frames in a queue anymore
}

void states::Running::Set() {
  const auto& kFloorClips =
      game_->res_manager().GetSpriteClips("floor", "floor");
  const auto& kBounds = contexts::graphics::GetBounds(registry_);
  const auto& kView =
      registry_
          ->view<components::identifiers::Dino, components::physics::RigidBody,
                 components::graphics::Sprite, components::graphics::Transform,
                 components::physics::Transform, components::physics::Collider,
                 components::graphics::Animation>();

  // Get animation frames for dino running
  const auto& kClips =
      game_->res_manager().GetSpriteClipsFromSlices("dino", name_);

  kView.each([&](auto& rigid_body, auto& sprite, auto& gtransform,
                 auto& ptransform, auto& collider, auto& animation) {
    rigid_body.velocity.y = 0;
    rigid_body.acceleration.y = 0;

    // Set up animation component
    animation.frames = std::vector<SDL_Rect>(kClips.begin(), kClips.end());
    animation.current_frame = 0;
    animation.elapsed = 0;
    animation.frame_duration = 120;  // ms per frame, adjust as needed

    // Set initial sprite frame
    sprite.clip = animation.frames[animation.current_frame];

    gtransform.position.w = sprite.clip.w;
    gtransform.position.h = sprite.clip.h;
    gtransform.position.y =
        kBounds.position.h - kFloorClips.front().h / 2 - gtransform.position.h;
    ptransform.position.w = sprite.clip.w;
    ptransform.position.h = sprite.clip.h;
    ptransform.position.y =
        kBounds.position.h - kFloorClips.front().h / 2 - ptransform.position.h;
    collider.box.x = sprite.clip.w / 8;
    collider.box.h = sprite.clip.h;
    collider.box.w = 3 * sprite.clip.w / 4;
  });
}

void states::Running::Update(const double dt) {
  // No custom animation logic needed; handled by Animation component and render
  // system
}
