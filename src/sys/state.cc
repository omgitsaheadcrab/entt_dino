/**
 * @file      state.cc
 * @brief     State system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-09-09
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#include "sys/state.h"

#include "comp/entities/dino.h"
#include "comp/entity_states/action.h"
#include "comp/graphics/sprite.h"
#include "core/game.h"
#include "events/dino/dead.h"
#include "events/dino/running.h"

void systems::State::OnInit() {
  dispatcher_->sink<events::dino::Dead>().connect<&systems::State::OnDead>(
      this);
  dispatcher_->sink<events::dino::Running>()
      .connect<&systems::State::OnRunning>(this);
}

void systems::State::OnDead(const events::dino::Dead&) {
  SetAction(Actions::dead);
}

void systems::State::OnRunning(const events::dino::Running&) {
  SetAction(Actions::running);
}

void systems::State::SetAction(const Actions kAction) {
  const auto& kClips = game_->res_manager().GetSpriteClips("dino");
  const auto& kView =
      registry_
          ->view<components::entities::Dino, components::graphics::Sprite>();

  kView.each([&](auto entity, auto sprite) {
    // Set running state and set sprite
    registry_->patch<components::entity_states::Action>(
        entity, [&](auto& action) { action.current = kAction; });
    registry_->patch<components::graphics::Sprite>(
        entity, [&](auto& sprite) { sprite.clip = kClips[kAction]; });
  });
}
