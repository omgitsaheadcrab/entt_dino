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

namespace states {

class Jumping : public omg::BaseState {
 public:
  Jumping() = default;
  virtual ~Jumping() = default;

  void Set() override;
  void OnJumpEnd();

 protected:
  void OnInit() override;
  void Update(const double_t dt) override;

 private:
  const double kGravity_ = 0.0015;  // 2*h_top/t_top
  const double kV0_ = -0.3;         // -2*h_top/(t_top^2)
  bool jumping_ = false;
  double jump_time_ = 150;
};

}  // namespace states

#endif  // ENTT_DINO_SRC_STATES_JUMPING_H_
