/**
 * @file      ducking.cc
 * @brief     Ducking state state
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-09-14
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#include "states/ducking.h"

#include <cstdint>

#include "comp/graphics/sprite.h"
#include "comp/graphics/transform.h"
#include "comp/identifiers/dino.h"
#include "comp/physics/collider.h"
#include "comp/physics/rigid_body.h"
#include "comp/physics/transform.h"
#include "core/game.h"
#include "ctx/game_states.h"
#include "ctx/graphics.h"

void states::Ducking::OnInit() {
  const auto& kClips =
      game_->res_manager().GetSpriteClipsFromSlices("dino", name_);
  for (auto& clip : kClips) {
    animation_frames_.push({clip});
  }
}

void states::Ducking::Set() {
  animation_elapsed_ = 0;
  const auto& kFloorClips =
      game_->res_manager().GetSpriteClips("floor", "floor");
  const auto& kBounds = contexts::graphics::GetBounds(registry_);
  const auto& kView = registry_->view<
      components::identifiers::Dino, components::physics::RigidBody,
      components::graphics::Sprite, components::graphics::Transform,
      components::physics::Transform, components::physics::Collider>();

  kView.each([&](auto& rigid_body, auto& sprite, auto& gtransform,
                 auto& ptransform, auto& collider) {
    sprite.clip = animation_frames_.front();
    rigid_body.velocity.y = 0;
    rigid_body.acceleration.y = 0;
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

void states::Ducking::Update(const double dt) {
  animation_elapsed_ += static_cast<uint32_t>(dt);
  const auto kBaseSpeed = contexts::game::GetSpeed(registry_).value;

  if (animation_elapsed_ >= kAnimation_base_duration_ * (1.0 - kBaseSpeed)) {
    animation_elapsed_ = 0;
    animation_frames_.push(animation_frames_.front());
    animation_frames_.pop();
  }

  const auto& kView =
      registry_
          ->view<components::identifiers::Dino, components::graphics::Sprite>();

  kView.each([&](auto& sprite) { sprite.clip = animation_frames_.front(); });
}
