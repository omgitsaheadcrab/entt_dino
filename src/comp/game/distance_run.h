/**
 * @file      distance_run.h
 * @brief     Distance run component
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-22
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_COMP_GAME_DISTANCE_RUN_H_
#define ENTT_DINO_SRC_COMP_GAME_DISTANCE_RUN_H_

#include <cstdint>

namespace components {

namespace game {

struct Distance {
  uint32_t value;
};

}  // namespace game

}  // namespace components

#endif  // ENTT_DINO_SRC_COMP_GAME_DISTANCE_RUN_H_
