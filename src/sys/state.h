/**
 * @file      states.h
 * @brief     State system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-09-09
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_SYS_STATE_H_
#define ENTT_DINO_SRC_SYS_STATE_H_

#include "comp/entity/states.h"
#include "core/base_state.h"
#include "core/base_system.h"
#include "events/dino/dead.h"
#include "events/dino/running.h"

namespace systems {

class State : public omg::BaseSystem {
 public:
  State() = default;
  ~State() = default;

  void Update(const double dt) override;

  void OnDead(const events::dino::Dead&);
  void OnRunning(const events::dino::Running&);

 protected:
  void OnInit() override;

 private:
  void AddState(std::unique_ptr<omg::BaseState> state, const States kState);
  bool SetCurrentState(const States kState);

  std::vector<std::unique_ptr<omg::BaseState>> states_;
  omg::BaseState* current_state_ = nullptr;
};

}  // namespace systems

#endif  // ENTT_DINO_SRC_SYS_STATE_H_
