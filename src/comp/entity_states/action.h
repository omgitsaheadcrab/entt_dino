/**
 * @file      actions.h
 * @brief     Entity action states
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-09-09
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_COMP_ENTITY_STATES_ACTIONS_H_
#define ENTT_DINO_SRC_COMP_ENTITY_STATES_ACTIONS_H_

#include <cstdint>

enum Actions { running, dead };

namespace components {

namespace entity_states {

struct Action {
  uint32_t current = Actions::running;
};

}  // namespace entity_states

}  // namespace components

#endif  // ENTT_DINO_SRC_COMP_ENTITY_STATES_ACTIONS_H_
