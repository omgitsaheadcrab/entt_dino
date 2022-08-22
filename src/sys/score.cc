/**
 * @file      score.cc
 * @brief     Scoring system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-22
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#include "ctx/game_states.h"
#include "sys/score.h"

void systems::score::Update(entt::registry* registry) {
  const auto kSpeedBoost = 0.02;
  const auto kSpeedBoostMultiple = 100;
  const auto kScore = contexts::game_states::GetScore(registry).value;
  const auto kDistanceScale = 20;  // Magic number to scale distance to make
                                   // score initially rise by ~10/sec
  if (contexts::game_states::GetDistance(registry).value / kDistanceScale >
      kScore) {
    contexts::game_states::IncrementScore(registry, 1);

    // Integer division to detect threshold cross
    if (kScore / kSpeedBoostMultiple <
        contexts::game_states::GetScore(registry).value / kSpeedBoostMultiple) {
      contexts::game_states::IncrementSpeed(registry, kSpeedBoost);
    }
  }
}
