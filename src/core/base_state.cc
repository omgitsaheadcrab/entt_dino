/**
 * @file      base_state.cc
 * @brief     Base state
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-09-14
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#include "core/base_state.h"

#include <entt/entity/registry.hpp>
#include <entt/signal/dispatcher.hpp>

#include "core/game.h"

States& omg::BaseState::type() { return type_; }

void omg::BaseState::Init(omg::Game* game, entt::registry* registry,
                          entt::dispatcher* dispatcher, const States state) {
  game_ = game;

  type_ = state;
  registry_ = registry;
  dispatcher_ = dispatcher;

  OnInit();
}
