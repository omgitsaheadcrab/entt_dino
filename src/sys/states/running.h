/**
 * @file      running.h
 * @brief     Running state system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-09-01
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_SYS_STATES_RUNNING_H_
#define ENTT_DINO_SRC_SYS_STATES_RUNNING_H_

#include "core/base_system.h"
#include "events/dino/running.h"

namespace systems {

namespace states {

class Running : public omg::BaseSystem {
 public:
  Running() = default;
  ~Running() = default;

  void OnRunning(const events::dino::Running&);

 protected:
  void OnInit() override;
};

}  // namespace states

}  // namespace systems

#endif  // ENTT_DINO_SRC_SYS_STATES_RUNNING_H_
