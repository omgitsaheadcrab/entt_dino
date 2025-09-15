/**
 * @file      collide.h
 * @brief     Collide system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2025-09-15
 * @copyright Copyright © 2025 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_SYS_COLLIDE_H_
#define ENTT_DINO_SRC_SYS_COLLIDE_H_

#include "core/base_system.h"

namespace systems {

class Collide : public omg::BaseSystem {
 public:
  Collide() = default;
  virtual ~Collide() = default;

  void Update(const double dt) override;

 private:
  bool EnemyCollision();
  void Resolve();
};

}  // namespace systems

#endif  // ENTT_DINO_SRC_SYS_COLLIDE_H_
