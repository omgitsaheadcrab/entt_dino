/**
 * @file      running.h
 * @brief     Running state
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-09-09
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_STATES_RUNNING_H_
#define ENTT_DINO_SRC_STATES_RUNNING_H_

#include <cstdint>
#include <queue>

#include "core/base_state.h"

namespace states {

class Running : public omg::BaseState {
 public:
  ~Running() = default;

  void Set() override;
  void Update(const double_t dt) override;

 private:
  uint32_t animation_elapsed_ = 0;
  uint32_t animation_duration_ = 0;
  const uint32_t animation_base_duration_ = 800;
  std::queue<uint32_t> animation_frames_;
};

}  // namespace states

#endif  // ENTT_DINO_SRC_STATES_RUNNING_H_
