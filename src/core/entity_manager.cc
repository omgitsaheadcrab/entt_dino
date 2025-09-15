/**
 * @file      entity_manager.cc
 * @brief     Entity manager
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2025-08-25
 * @copyright Copyright © 2025 Tobias Backer Dirks
 */

#include "core/entity_manager.h"

#include <memory>
#include <utility>

#include "core/base_system.h"
#include "core/game.h"

void omg::EntityManager::Init(omg::Game* game) { game_ = game; }

void omg::EntityManager::AddUpdateSystem(
    std::unique_ptr<omg::BaseSystem> system) {
  system->Init(game_, &registry_, &dispatcher_);
  update_systems_.push_back(std::move(system));
}

void omg::EntityManager::AddRenderSystem(
    std::unique_ptr<omg::BaseSystem> system) {
  system->Init(game_, &registry_, &dispatcher_);
  render_systems_.push_back(std::move(system));
}

void omg::EntityManager::OnUpdate(const double dt) {
  for (auto& system : update_systems_) {
    system->Update(dt);
  }
}

void omg::EntityManager::OnRender(const double alpha) {
  for (auto& system : render_systems_) {
    system->Update(alpha);
  }
}

entt::dispatcher* omg::EntityManager::dispatcher() { return &dispatcher_; }

entt::registry* omg::EntityManager::registry() { return &registry_; }
