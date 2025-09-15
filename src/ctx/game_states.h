/**
 * @file      game_states.h
 * @brief     Game state contexts
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2025-09-15
 * @copyright Copyright © 2025 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_CTX_GAME_STATES_H_
#define ENTT_DINO_SRC_CTX_GAME_STATES_H_

#include <cstdint>
#include <string>

#include <entt/entity/registry.hpp>

#include "comp/game/dark.h"
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

constexpr auto GetHighscore = &contexts::Get<components::game::Highscore>;
constexpr auto SetHighscore =
    &contexts::Set<components::game::Highscore, const uint32_t>;

constexpr auto GetSpeed = &contexts::Get<components::game::Speed>;
constexpr auto SetSpeed = &contexts::Set<components::game::Speed, const double>;

constexpr auto GetDark = &contexts::GetBool<components::game::Dark>;
constexpr auto SetDark = &contexts::SetBool<components::game::Dark>;
constexpr auto ToggleDark = &contexts::ToggleBool<components::game::Dark>;

constexpr auto GetState = &contexts::Get<components::game::State>;
constexpr auto SetState =
    &contexts::Set<components::game::State, const std::string>;

}  // namespace game

}  // namespace contexts

#endif  // ENTT_DINO_SRC_CTX_GAME_STATES_H_
