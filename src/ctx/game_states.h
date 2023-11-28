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

#include "comp/game/dark.h"
#include "comp/game/distance_run.h"
#include "comp/game/highscore.h"
#include "comp/game/score.h"
#include "comp/game/speed.h"
#include "comp/game/state.h"
#include "ctx/context.h"

namespace contexts {

namespace game {

constexpr auto GetScore = &contexts::Get<components::game::Score>;
constexpr auto SetScore =
    &contexts::Set<components::game::Score, const uint32_t>;
constexpr auto IncrementScore =
    &contexts::Increment<components::game::Score, uint32_t>;

constexpr auto GetDistance = &contexts::Get<components::game::Distance>;
constexpr auto SetDistance =
    &contexts::Set<components::game::Distance, const uint32_t>;
constexpr auto IncrementDistance =
    &contexts::Increment<components::game::Distance, uint32_t>;

constexpr auto GetHighscore = &contexts::Get<components::game::Highscore>;
constexpr auto SetHighscore =
    &contexts::Set<components::game::Highscore, const uint32_t>;

constexpr auto GetSpeed = &contexts::Get<components::game::Speed>;
constexpr auto SetSpeed = &contexts::Set<components::game::Speed, const double>;
constexpr auto IncrementSpeed =
    &contexts::Increment<components::game::Speed, double>;

constexpr auto GetDark = &contexts::GetBool<components::game::Dark>;
constexpr auto SetDark = &contexts::SetBool<components::game::Dark>;
constexpr auto ToggleDark = &contexts::ToggleBool<components::game::Dark>;

constexpr auto GetState = &contexts::Get<components::game::State>;
constexpr auto SetState =
    &contexts::Set<components::game::State, const std::string>;

}  // namespace game

}  // namespace contexts

#endif  // ENTT_DINO_SRC_CTX_GAME_STATES_H_
