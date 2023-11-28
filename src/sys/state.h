/**
 * @file      states.h
 * @brief     State system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-09-09
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_SYS_STATE_H_
#define ENTT_DINO_SRC_SYS_STATE_H_

#include <memory>
#include <string>
#include <vector>

#include "core/base_state.h"
#include "core/base_system.h"
#include "events/dino/dead.h"
#include "events/dino/jumping.h"
#include "events/dino/running.h"

namespace systems {

class State : public omg::BaseSystem {
 public:
  State() = default;
  virtual ~State() = default;

  void Update(const double dt) override;

  void OnDead(const events::dino::Dead&);
  void OnRunning(const events::dino::Running&);
  void OnJumping(const events::dino::JumpStart&);

 protected:
  void OnInit() override;

 private:
  void AddState(std::unique_ptr<omg::BaseState> state);
  bool IsActiveState(const std::string kStateName);
  bool SetCurrentState(const std::string kStateName);

  std::vector<std::unique_ptr<omg::BaseState>> states_;
  omg::BaseState* current_state_ = nullptr;
};

}  // namespace systems

#endif  // ENTT_DINO_SRC_SYS_STATE_H_
