/**
 * @file      base_system.h
 * @brief     Base system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-25
 * @copyright Copyright © 2022 Tobias Backer Dirks
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
  ~BaseSystem() = default;

  void Init(omg::Game* game, entt::registry* registry,
            entt::dispatcher* dispatcher);

  virtual void Update(const double dt) = 0;

 protected:
  virtual void OnInit() = 0;

  omg::Game* game_;
  entt::registry* registry_;
  entt::dispatcher* dispatcher_;
};

}  // namespace omg

#endif  // ENTT_DINO_SRC_CORE_BASE_SYSTEM_H_
