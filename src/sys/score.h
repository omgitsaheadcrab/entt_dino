/**
 * @file      score.h
 * @brief     Scoring system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-22
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_SYS_SCORE_H_
#define ENTT_DINO_SRC_SYS_SCORE_H_

#include "core/base_system.h"

namespace systems {

class Score : public omg::BaseSystem {
 public:
  Score() = default;
  ~Score() = default;

  void Update(const double dt) override;
};

}  // namespace systems

#endif  // ENTT_DINO_SRC_SYS_SCORE_H_
