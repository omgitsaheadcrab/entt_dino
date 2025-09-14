/**
 * @file      jumping.cc
 * @brief     Jumping state
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-09-14
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#include "states/jumping.h"

#include "comp/graphics/animation.h"
#include "comp/graphics/sprite.h"
#include "comp/graphics/transform.h"
#include "comp/identifiers/dino.h"
#include "comp/physics/collider.h"
#include "comp/physics/rigid_body.h"
#include "comp/physics/transform.h"
#include "core/game.h"
#include "events/dino/jumping.h"

void states::Jumping::OnInit() {
  dispatcher_->sink<events::dino::JumpEnd>()
      .connect<&states::Jumping::OnJumpEnd>(this);
  dispatcher_->sink<events::dino::JumpDuck>()
      .connect<&states::Jumping::OnJumpDuck>(this);
}

void states::Jumping::OnJumpEnd() { jumping_ = false; }

void states::Jumping::OnJumpDuck() { jump_ducking_ = true; }

void states::Jumping::Set() {
  const auto& kClips =
      game_->res_manager().GetSpriteClipsFromSlices("dino", name_);
  const auto& kView = registry_->view<
      components::identifiers::Dino, components::graphics::Sprite,
      components::physics::RigidBody, components::graphics::Transform,
      components::physics::Transform, components::physics::Collider,
      components::graphics::Animation>();

  kView.each([&](auto& sprite, auto& rigid_body, auto& gtransform,
                 auto& ptransform, auto& collider, auto& animation) {
    // For jumping, use only the first frame (not animated)
    animation.frames = {kClips.front()};
    animation.current_frame = 0;
    animation.elapsed = 0;
    animation.frame_duration = 1000;  // Large value, disables animation

    sprite.clip = animation.frames[animation.current_frame];
    rigid_body.acceleration.y = kGravity_;
    rigid_body.velocity.y = kV0_;
    gtransform.position.w = sprite.clip.w;
    gtransform.position.h = sprite.clip.h;
    ptransform.position.w = sprite.clip.w;
    ptransform.position.h = sprite.clip.h;
    collider.box.x = sprite.clip.w / 8;
    collider.box.h = sprite.clip.h;
    collider.box.w = 3 * sprite.clip.w / 4;
  });

  jump_ducking_ = false;
  jumping_ = true;
  jump_time_ = 150;
  Mix_PlayChannel(-1, game_->res_manager().GetSound("jump"), 0);
}

void states::Jumping::Update(const double dt) {
  const auto& kView = registry_->view<components::identifiers::Dino,
                                      components::physics::RigidBody>();

  double jump_gravity = kGravity_;
  if (jumping_ && jump_time_ > 0) {
    jump_gravity = -0.0005 * kGravity_;
  }
  if (jump_ducking_) {
    jump_gravity *= 5;
  }
  kView.each([&](auto& rigid_body) {
    rigid_body.acceleration.y = jump_gravity;
    rigid_body.velocity.y += rigid_body.acceleration.y * dt;
  });
  jump_time_ -= dt;
}
