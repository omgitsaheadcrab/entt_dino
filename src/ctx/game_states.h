/**
 * @file      game_states.h
 * @brief     Game state contexts
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-11
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_CTX_GAME_STATES_H_
#define ENTT_DINO_SRC_CTX_GAME_STATES_H_

#include <cstdint>

#include <entt/entity/registry.hpp>

#include "comp/game_states/highscore.h"
#include "comp/game_states/over.h"
#include "comp/game_states/score.h"
#include "comp/game_states/speed.h"
#include "ctx/context.h"

namespace contexts {

namespace game_states {

constexpr auto GetScore = &contexts::Get<components::game_states::Score>;
constexpr auto SetScore =
    &contexts::Set<components::game_states::Score, const uint32_t>;
constexpr auto IncrementScore =
    &contexts::Increment<components::game_states::Score>;

constexpr auto GetHighscore =
    &contexts::Get<components::game_states::Highscore>;
constexpr auto SetHighscore =
    &contexts::Set<components::game_states::Highscore, const uint32_t>;

constexpr auto GetSpeed = &contexts::Get<components::game_states::Speed>;
constexpr auto SetSpeed =
    &contexts::Set<components::game_states::Speed, const uint32_t>;
constexpr auto IncrementSpeed =
    &contexts::Increment<components::game_states::Speed>;

constexpr auto GetOver = &contexts::GetBool<components::game_states::Over>;
constexpr auto SetOver = &contexts::SetBool<components::game_states::Over>;

}  // namespace game_states

}  // namespace contexts

#endif  // ENTT_DINO_SRC_CTX_GAME_STATES_H_
