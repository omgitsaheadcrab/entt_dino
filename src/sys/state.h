/**
 * @file      states.h
 * @brief     State system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2025-09-15
 * @copyright Copyright © 2025 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_SYS_STATE_H_
#define ENTT_DINO_SRC_SYS_STATE_H_

#include <memory>
#include <string>
#include <vector>

#include "core/base_state.h"
#include "core/base_system.h"

namespace systems {

class State : public omg::BaseSystem {
 public:
  State() = default;
  virtual ~State() = default;

  void Update(const double dt) override;

 protected:
  void OnInit() override;

 private:
  bool IsActiveState(const std::string kStateName);
  bool SetCurrentState(const std::string kStateName);
  void AddState(std::unique_ptr<omg::BaseState> state);
  void OnDead();
  void OnJumping();
  void OnRestart();
  void OnRunning();
  void OnDucking();

  std::vector<std::unique_ptr<omg::BaseState>> states_;
  omg::BaseState* current_state_ = nullptr;
};

}  // namespace systems

#endif  // ENTT_DINO_SRC_SYS_STATE_H_
