/**
 * @file      score.h
 * @brief     Score component
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2025-09-15
 * @copyright Copyright © 2025 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_COMP_GAME_SCORE_H_
#define ENTT_DINO_SRC_COMP_GAME_SCORE_H_

#include <cstdint>

namespace components {

namespace game {

struct Score {
  uint32_t value;
};

}  // namespace game

}  // namespace components

#endif  // ENTT_DINO_SRC_COMP_GAME_SCORE_H_
