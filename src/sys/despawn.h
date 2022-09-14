/**
 * @file      despawn.h
 * @brief     Despawn system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-11-18
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_SYS_DESPAWN_H_
#define ENTT_DINO_SRC_SYS_DESPAWN_H_

#include "core/base_system.h"

namespace systems {

class Despawn : public omg::BaseSystem {
 public:
  Despawn() = default;
  ~Despawn() = default;

  void Update(const double dt) override;
};

}  // namespace systems

#endif  // ENTT_DINO_SRC_SYS_DESPAWN_H_
