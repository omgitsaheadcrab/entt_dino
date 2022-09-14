/**
 * @file      dead.h
 * @brief     Dead state
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-09-09
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_STATES_DEAD_H_
#define ENTT_DINO_SRC_STATES_DEAD_H_

#include "core/base_state.h"

namespace states {

class Dead : public omg::BaseState {
 public:
  ~Dead() = default;

  void Set() override;
};

}  // namespace states

#endif  // ENTT_DINO_SRC_STATES_DEAD_H_
