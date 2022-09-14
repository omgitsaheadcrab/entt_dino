/**
 * @file      speed.h
 * @brief     Game speed component
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-11
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_COMP_GAME_SPEED_H_
#define ENTT_DINO_SRC_COMP_GAME_SPEED_H_

#include <cstdint>

namespace components {

namespace game {

struct Speed {
  double value;
};

}  // namespace game

}  // namespace components

#endif  // ENTT_DINO_SRC_COMP_GAME_SPEED_H_
