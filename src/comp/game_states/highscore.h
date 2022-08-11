/**
 * @file      highscore.h
 * @brief     Highscore component
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-11
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_COMP_GAME_STATES_HIGHSCORE_H_
#define ENTT_DINO_SRC_COMP_GAME_STATES_HIGHSCORE_H_

#include <cstdint>

namespace components {

namespace game_states {

struct Highscore
{
  uint32_t value;
};

}  // namespace game_states

}  // namespace components


#endif  // ENTT_DINO_SRC_COMP_GAME_STATES_HIGHSCORE_H_
