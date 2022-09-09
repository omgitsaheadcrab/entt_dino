/**
 * @file      states.h
 * @brief     State system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-09-09
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_SYS_STATE_H_
#define ENTT_DINO_SRC_SYS_STATE_H_

#include <cstdint>

#include "core/base_system.h"
#include "events/dino/dead.h"
#include "events/dino/running.h"

namespace systems {

class State : public omg::BaseSystem {
 public:
  State() = default;
  ~State() = default;

  void OnDead(const events::dino::Dead&);
  void OnRunning(const events::dino::Running&);

 protected:
  void OnInit() override;
};

}  // namespace systems

#endif  // ENTT_DINO_SRC_SYS_STATE_H_
