/**
 * @file      base_state.cc
 * @brief     Base state
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2025-09-14
 * @copyright Copyright © 2025 Tobias Backer Dirks
 */

#include "core/base_state.h"

#include <string>

#include <entt/entity/registry.hpp>
#include <entt/signal/dispatcher.hpp>

#include "core/game.h"

omg::BaseState::BaseState(const char* name) : name_ {name} {}

void omg::BaseState::Init(omg::Game* game, entt::registry* registry,
                          entt::dispatcher* dispatcher) {
  game_ = game;

  registry_ = registry;
  dispatcher_ = dispatcher;

  OnInit();
}

std::string& omg::BaseState::name() { return name_; }
