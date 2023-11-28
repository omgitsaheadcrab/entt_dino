/**
 * @file      state.cc
 * @brief     State system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-09-09
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#include "sys/state.h"

#include <memory>
#include <string>
#include <utility>

#include "comp/graphics/sprite.h"
#include "comp/identifiers/dino.h"
#include "core/game.h"
#include "events/dino/dead.h"
#include "events/dino/jumping.h"
#include "events/dino/running.h"
#include "states/dead.h"
#include "states/jumping.h"
#include "states/running.h"

#include "ctx/game_states.h"


void systems::State::OnInit() {
  dispatcher_->sink<events::dino::Dead>().connect<&systems::State::OnDead>(
      this);
  dispatcher_->sink<events::dino::Running>()
      .connect<&systems::State::OnRunning>(this);
  dispatcher_->sink<events::dino::JumpStart>()
      .connect<&systems::State::OnJumping>(this);

  AddState(std::make_unique<states::Running>("running"));
  AddState(std::make_unique<states::Jumping>("jumping"));
  AddState(std::make_unique<states::Dead>("dead"));

  SetCurrentState("running");
}

void systems::State::Update(const double dt) { current_state_->Update(dt); }

void systems::State::OnDead(const events::dino::Dead&) {
  if (!IsActiveState("dead")) SetCurrentState("dead");
}

void systems::State::OnRunning(const events::dino::Running&) {
  if (!IsActiveState("running")) SetCurrentState("running");
}

void systems::State::OnJumping(const events::dino::JumpStart&) {
  if (!IsActiveState("jumping")) SetCurrentState("jumping");
}

void systems::State::AddState(std::unique_ptr<omg::BaseState> state) {
  state->Init(game_, registry_, dispatcher_);

  states_.push_back(std::move(state));
}

bool systems::State::IsActiveState(const std::string kStateName) {
  if (current_state_->name() == kStateName) {
    return true;
  }
  return false;
}

bool systems::State::SetCurrentState(const std::string kStateName) {
  for (auto& state : states_) {
    if (state->name() == kStateName) {
      current_state_ = state.get();
      current_state_->Set();
      contexts::game::SetState(registry_, kStateName);
      return true;
    }
  }
  return false;
}
