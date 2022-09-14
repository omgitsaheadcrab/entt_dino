/**
 * @file      running.cc
 * @brief     Running state state
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-09-14
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#include "states/running.h"

#include <cstdint>
#include <iostream>

#include "comp/entity/states.h"
#include "comp/graphics/sprite.h"
#include "comp/identifiers/dino.h"
#include "core/game.h"
#include "ctx/game_states.h"

void states::Running::Set() {
  animation_frames_.push(2);
  animation_frames_.push(3);
}

void states::Running::Update(const double dt) {
  elapsed_ += static_cast<uint32_t>(dt);
  animation_elapsed_ += static_cast<uint32_t>(dt);
  animation_duration_ =
      animation_base_duration_ * contexts::game::GetSpeed(registry_).value;

  if (animation_elapsed_ >= animation_duration_) {
    animation_elapsed_ -= animation_duration_;

    animation_frames_.push(animation_frames_.front());
    animation_frames_.pop();
  }

  const auto& kClips = game_->res_manager().GetSpriteClips("dino");
  const auto& kView =
      registry_
          ->view<components::identifiers::Dino, components::graphics::Sprite>();

  kView.each([&](auto entity, auto sprite) {
    // Set running state and set sprite
    registry_->patch<components::entity::State>(
        entity, [&](auto& state) { state.current = type_; });
    registry_->patch<components::graphics::Sprite>(entity, [&](auto& sprite) {
      sprite.clip = kClips[animation_frames_.front()];
    });
  });
}
