/**
 * @file      running.h
 * @brief     Running state
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-09-09
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_STATES_RUNNING_H_
#define ENTT_DINO_SRC_STATES_RUNNING_H_

#include "core/base_state.h"

namespace states {

class Running : public omg::BaseState {
 public:
  ~Running() = default;

  void Set() override;
};

}  // namespace states

#endif  // ENTT_DINO_SRC_STATES_RUNNING_H_
