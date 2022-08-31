/**
 * @file      dead.h
 * @brief     Dead state system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-31
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_SYS_STATES_DEAD_H_
#define ENTT_DINO_SRC_SYS_STATES_DEAD_H_

#include "core/base_system.h"
#include "events/dino/dead.h"

namespace systems {

namespace states {

class Dead : public omg::BaseSystem {
 public:
  Dead() = default;
  ~Dead() = default;

  void OnDead(const events::dino::Dead&);

 protected:
  void OnInit() override;
};

}  // namespace states

}  // namespace systems

#endif  // ENTT_DINO_SRC_SYS_STATES_DEAD_H_
