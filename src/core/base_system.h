/**
 * @file      base_system.h
 * @brief     Base system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2025-09-15
 * @copyright Copyright © 2025 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_CORE_BASE_SYSTEM_H_
#define ENTT_DINO_SRC_CORE_BASE_SYSTEM_H_

#include <entt/entity/registry.hpp>
#include <entt/signal/dispatcher.hpp>

#include "core/fwd.h"

namespace omg {

class BaseSystem {
 public:
  BaseSystem() = default;
  virtual ~BaseSystem() = default;

  void Init(omg::Game* game, entt::registry* registry,
            entt::dispatcher* dispatcher);

  inline virtual void Update(const double dt) {}

 protected:
  inline virtual void OnInit() {}

  omg::Game* game_;
  entt::registry* registry_;
  entt::dispatcher* dispatcher_;
};

}  // namespace omg

#endif  // ENTT_DINO_SRC_CORE_BASE_SYSTEM_H_
