/**
 * @file      move.h
 * @brief     Move system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-24
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_SYS_MOVE_H_
#define ENTT_DINO_SRC_SYS_MOVE_H_

#include "core/base_system.h"

namespace systems {

class Move : public omg::BaseSystem {
 public:
  Move() = default;
  ~Move() = default;

  void Update(const double dt) override;
};

}  // namespace systems

#endif  // ENTT_DINO_SRC_SYS_MOVE_H_
