/**
 * @file      state.h
 * @brief     Game state component
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-22
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_COMP_GAME_STATE_H_
#define ENTT_DINO_SRC_COMP_GAME_STATE_H_

#include <string>

namespace components {

namespace game {

struct State {
  std::string value;
};

}  // namespace game

}  // namespace components

#endif  // ENTT_DINO_SRC_COMP_GAME_STATE_H_
