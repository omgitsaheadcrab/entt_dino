/**
 * @file      jumping.cc
 * @brief     Jumping state
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
#include "events/dino/jumping.h"

void states::Jumping::OnInit() {
  dispatcher_->sink<events::dino::JumpEnd>()
      .connect<&states::Jumping::OnJumpEnd>(this);
}

void states::Jumping::OnJumpEnd() {
  jumping_ = false;
}

void states::Jumping::Set() {
  const auto& kClips = game_->res_manager().GetSpriteClips("dino", "jumping");
  const auto& kView =
      registry_->view<components::identifiers::Dino, components::entity::State,
                      components::graphics::Sprite,
                      components::physics::RigidBody>();

  kView.each([&](auto& state, auto& sprite, auto& rigid_body) {
    state.current = type_;
    sprite.clip = kClips.front();
    rigid_body.acceleration.y = kGravity_;
    rigid_body.velocity.y = kV0_;
  });

  jumping_ = true;
  jump_time_ = 150;
}

void states::Jumping::Update(const double dt) {
  const auto& kView = registry_->view<components::identifiers::Dino,
                                      components::physics::RigidBody>();

  double jump_gravity = kGravity_;
  if (jumping_ && jump_time_ > 0) {
    jump_gravity = -0.0005 * kGravity_;
  }
  kView.each([&](auto& rigid_body) {
    rigid_body.acceleration.y = jump_gravity;
    rigid_body.velocity.y += rigid_body.acceleration.y * dt;
  });
  jump_time_ -= dt;
}
