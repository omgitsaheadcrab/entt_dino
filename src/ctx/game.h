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

namespace contexts {

namespace game {

components::game_states::Speed GetSpeed(entt::registry* registry);

void SetSpeed(entt::registry* registry, const uint32_t speed);

components::game_states::Score GetScore(entt::registry* registry);

void SetScore(entt::registry* registry, const uint32_t score);

components::game_states::Highscore GetHighScore(entt::registry* registry);

void SetHighScore(entt::registry* registry, const uint32_t score);

bool GetOver(entt::registry* registry);

void SetOver(entt::registry* registry, const bool over);

}  // namespace game

}  // namespace contexts

#endif  // ENTT_DINO_SRC_CTX_GAME_H_
