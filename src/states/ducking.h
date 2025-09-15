/**
 * @file      ducking.h
 * @brief     Ducking state
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2025-09-15
 * @copyright Copyright © 2025 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_STATES_DUCKING_H_
#define ENTT_DINO_SRC_STATES_DUCKING_H_

#include <SDL2/SDL_rect.h>

#include <cstdint>
#include <queue>

#include "core/base_state.h"

using omg::BaseState;

namespace states {

class Ducking : public BaseState {
  using BaseState::BaseState;

 public:
  virtual ~Ducking() = default;

  void Set() override;
  void Update(const double_t dt) override;

 protected:
  void OnInit() override;

 private:
  uint32_t animation_elapsed_ = 0;
  std::queue<SDL_Rect> animation_frames_;

  static constexpr uint32_t kAnimation_base_duration_ = 200;
};

}  // namespace states

#endif  // ENTT_DINO_SRC_STATES_DUCKING_H_
