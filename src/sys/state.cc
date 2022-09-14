/**
 * @file      state.cc
 * @brief     State system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-09-09
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#include "sys/state.h"

#include <memory>
#include <utility>

#include "comp/entity/states.h"
#include "comp/graphics/sprite.h"
#include "comp/identifiers/dino.h"
#include "core/game.h"
#include "events/dino/dead.h"
#include "events/dino/running.h"
#include "states/dead.h"
#include "states/running.h"

void systems::State::OnInit() {
  dispatcher_->sink<events::dino::Dead>().connect<&systems::State::OnDead>(
      this);
  dispatcher_->sink<events::dino::Running>()
      .connect<&systems::State::OnRunning>(this);

  AddState(std::make_unique<states::Running>(), States::running);
  AddState(std::make_unique<states::Dead>(), States::dead);

  SetCurrentState(States::running);
}

void systems::State::Update(const double dt) { current_state_->Update(dt); }

void systems::State::OnDead(const events::dino::Dead&) {
  SetCurrentState(States::dead);
}

void systems::State::OnRunning(const events::dino::Running&) {
  SetCurrentState(States::running);
}

void systems::State::AddState(std::unique_ptr<omg::BaseState> state,
                              const States kStateType) {
  state->Init(game_, registry_, dispatcher_, kStateType);

  states_.push_back(std::move(state));
}

bool systems::State::SetCurrentState(const States kState) {
  for (auto& state : states_) {
    if (state->type() == kState) {
      current_state_ = state.get();
      current_state_->Set();
      return true;
    }
  }
  return false;
}
