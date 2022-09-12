/**
 * @file      base_system.cc
 * @brief     Base system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-25
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#include "core/base_system.h"

#include <entt/entity/registry.hpp>
#include <entt/signal/dispatcher.hpp>

#include "core/game.h"

void omg::BaseSystem::Init(omg::Game* game, entt::registry* registry,
                           entt::dispatcher* dispatcher) {
  game_ = game;

  registry_ = registry;
  dispatcher_ = dispatcher;

  OnInit();
}
