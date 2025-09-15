/**
 * @file      score.h
 * @brief     Scoring system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2025-09-15
 * @copyright Copyright © 2025 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_SYS_SCORE_H_
#define ENTT_DINO_SRC_SYS_SCORE_H_

#include <cstdint>

#include "core/base_system.h"

namespace systems {

class Score : public omg::BaseSystem {
 public:
  Score() = default;
  virtual ~Score() = default;

  void Update(const double dt) override;

 protected:
  void OnInit() override;

 private:
  void OnDead();
  void OnRestart();

  static constexpr double kSpeedBoost_ = 0.02;
  static constexpr uint32_t kSpeedBoostMultiple_ = 100;
  static constexpr uint32_t kDistanceScale_ =
      20;  // Magic number to scale distance to make
           // score initially rise by ~10/sec
  uint32_t distance_;
  uint32_t highscore_;
  uint32_t score_;
  double speed_;
};

}  // namespace systems

#endif  // ENTT_DINO_SRC_SYS_SCORE_H_
