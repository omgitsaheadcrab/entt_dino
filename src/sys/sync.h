/**
 * @file      sync.h
 * @brief     Synchronize graphics with physics
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2025-09-15
 * @copyright Copyright © 2025 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_SYS_SYNC_H_
#define ENTT_DINO_SRC_SYS_SYNC_H_

#include "core/base_system.h"

namespace systems {

class Sync : public omg::BaseSystem {
 public:
  Sync() = default;
  virtual ~Sync() = default;

  void Update(const double dt) override;
};

}  // namespace systems

#endif  // ENTT_DINO_SRC_SYS_SYNC_H_
