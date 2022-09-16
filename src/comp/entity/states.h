/**
 * @file      states.h
 * @brief     Entity states
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-09-09
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_COMP_ENTITY_STATES_H_
#define ENTT_DINO_SRC_COMP_ENTITY_STATES_H_

#include <cstdint>

enum States { dead, running, jumping };

namespace components {

namespace entity {

struct State {
  uint32_t current = States::running;
};

}  // namespace entity

}  // namespace components

#endif  // ENTT_DINO_SRC_COMP_ENTITY_STATES_H_
