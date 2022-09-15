/**
 * @file      base_state.h
 * @brief     Base state
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-09-14
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_CORE_BASE_STATE_H_
#define ENTT_DINO_SRC_CORE_BASE_STATE_H_

#include <entt/entity/registry.hpp>
#include <entt/signal/dispatcher.hpp>

#include "comp/entity/states.h"
#include "core/fwd.h"

namespace omg {

class BaseState {
 public:
  BaseState() = default;
  virtual ~BaseState() = default;

  States type();

  void Init(omg::Game* game, entt::registry* registry,
            entt::dispatcher* dispatcher, const States state);

  inline virtual void Set() {}
  inline virtual void Update(const double dt) {}

 protected:
  inline virtual void OnInit() {}

  States type_;
  omg::Game* game_;
  entt::registry* registry_;
  entt::dispatcher* dispatcher_;
};

}  // namespace omg

#endif  // ENTT_DINO_SRC_CORE_BASE_STATE_H_
