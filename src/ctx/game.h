/**
 * @file      game.h
 * @brief     Game contexts
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-11
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_CTX_GAME_H_
#define ENTT_DINO_SRC_CTX_GAME_H_

#include <cstdint>

#include <entt/entity/registry.hpp>

#include "comp/game_states/highscore.h"
#include "comp/game_states/over.h"
#include "comp/game_states/score.h"
#include "comp/game_states/speed.h"
#include "ctx/context.h"

namespace contexts {

namespace game {

constexpr auto GetScore = &contexts::get<components::game_states::Score>;
constexpr auto GetHighscore =
    &contexts::get<components::game_states::Highscore>;
constexpr auto GetSpeed = &contexts::get<components::game_states::Speed>;
constexpr bool GetOver = &contexts::get_bool<components::game_states::Over>;

constexpr auto SetScore =
    &contexts::set<components::game_states::Score, const uint32_t>;
constexpr auto SetHighscore =
    &contexts::set<components::game_states::Highscore, const uint32_t>;
constexpr auto SetSpeed =
    &contexts::set<components::game_states::Speed, const uint32_t>;
constexpr auto SetOver = &contexts::set_bool<components::game_states::Over>;

}  // namespace game

}  // namespace contexts

#endif  // ENTT_DINO_SRC_CTX_GAME_H_
