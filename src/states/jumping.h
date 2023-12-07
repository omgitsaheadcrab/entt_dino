/**
 * @file      jumping.h
 * @brief     Jumping state
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-09-09
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_STATES_JUMPING_H_
#define ENTT_DINO_SRC_STATES_JUMPING_H_

#include "core/base_state.h"

using omg::BaseState;

namespace states {

class Jumping : public BaseState {
  using BaseState::BaseState;

 public:
  virtual ~Jumping() = default;

  void Set() override;

 protected:
  void OnInit() override;
  void Update(const double_t dt) override;
  void OnJumpEnd();
  void OnJumpDuck();

 private:
  const double kGravity_ = 0.0015;  // 2*h_top/t_top
  const double kV0_ = -0.3;         // -2*h_top/(t_top^2)
  bool jump_ducking_ = false;
  bool jumping_ = false;
  double jump_time_ = 150;
};

}  // namespace states

#endif  // ENTT_DINO_SRC_STATES_JUMPING_H_
