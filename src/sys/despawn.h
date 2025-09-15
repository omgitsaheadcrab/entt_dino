/**
 * @file      despawn.h
 * @brief     Despawn system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2025-09-15
 * @copyright Copyright © 2025 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_SYS_DESPAWN_H_
#define ENTT_DINO_SRC_SYS_DESPAWN_H_

#include "core/base_system.h"
#include "events/entity/despawn.h"

namespace systems {

class Despawn : public omg::BaseSystem {
 public:
  Despawn() = default;
  virtual ~Despawn() = default;

 protected:
  void OnInit() override;

 private:
  void OnDespawn(const events::entity::Despawn& despawn);
  void OnRestart();
};

}  // namespace systems

#endif  // ENTT_DINO_SRC_SYS_DESPAWN_H_
