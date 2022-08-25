/**
 * @file      entity_manager.h
 * @brief     Entity manager
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-25
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_CORE_ENTITY_MANAGER_H_
#define ENTT_DINO_SRC_CORE_ENTITY_MANAGER_H_

#include <memory>
#include <vector>

#include <entt/entity/registry.hpp>
#include <entt/signal/dispatcher.hpp>

#include "core/base_system.h"
#include "core/fwd.h"

namespace omg {

class EntityManager {
 public:
  EntityManager() = default;
  ~EntityManager() = default;

  void Init(omg::Game* game);
  void OnUpdate(const double dt);
  void OnRender(const double alpha);

  void AddUpdateSystem(std::unique_ptr<omg::BaseSystem>);
  void AddRenderSystem(std::unique_ptr<omg::BaseSystem>);

  entt::dispatcher* dispatcher();
  entt::registry* registry();

 private:
  omg::Game* game_;

  entt::dispatcher dispatcher_;
  entt::registry registry_;

  std::vector<std::unique_ptr<omg::BaseSystem>> update_systems_;
  std::vector<std::unique_ptr<omg::BaseSystem>> render_systems_;
};

}  // namespace omg

#endif  // ENTT_DINO_SRC_CORE_ENTITY_MANAGER_H_
