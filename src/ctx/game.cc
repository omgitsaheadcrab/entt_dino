/**
 * @file      game.cc
 * @brief     Game contexts
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-11
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#include "ctx/game.h"

#include <cstdint>

#include <entt/entity/registry.hpp>

#include "comp/game_states/highscore.h"
#include "comp/game_states/over.h"
#include "comp/game_states/score.h"
#include "comp/game_states/speed.h"
#include "comp/graphics/fps.h"

components::game_states::Speed contexts::game::GetSpeed(
    entt::registry* registry) {
  return registry->ctx().get<const components::game_states::Speed>();
}

void contexts::game::SetSpeed(entt::registry* registry, const uint32_t speed) {
  registry->ctx().insert_or_assign(components::game_states::Speed {speed});
}

components::game_states::Score contexts::game::GetScore(
    entt::registry* registry) {
  return registry->ctx().get<const components::game_states::Score>();
}

void contexts::game::SetScore(entt::registry* registry, const uint32_t score) {
  registry->ctx().insert_or_assign(components::game_states::Score {score});
}

components::game_states::Highscore contexts::game::GetHighScore(
    entt::registry* registry) {
  return registry->ctx().get<const components::game_states::Highscore>();
}

void contexts::game::SetHighScore(entt::registry* registry,
                                  const uint32_t score) {
  registry->ctx().insert_or_assign(components::game_states::Highscore {score});
}

bool contexts::game::GetOver(entt::registry* registry) {
  return registry->ctx().contains<const components::game_states::Over>();
}

void contexts::game::SetOver(entt::registry* registry, const bool over) {
  if (over) {
    registry->ctx().insert_or_assign(components::game_states::Over {});
  } else {
    registry->ctx().erase<components::game_states::Over>();
  }
}
