/**
 * @file      score.cc
 * @brief     Scoring system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-22
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#include "sys/score.h"

#include "ctx/game_states.h"

void systems::Score::Update(const double dt) {
  const auto kSpeedBoost = 0.02;
  const auto kSpeedBoostMultiple = 100;
  const auto kScore = contexts::game_states::GetScore(registry_).value;
  const auto kDistanceScale = 20;  // Magic number to scale distance to make
                                   // score initially rise by ~10/sec
  if (contexts::game_states::GetDistance(registry_).value / kDistanceScale >
      kScore) {
    contexts::game_states::IncrementScore(registry_, 1);

    // Integer division to detect threshold cross
    if (kScore / kSpeedBoostMultiple <
        contexts::game_states::GetScore(registry_).value /
            kSpeedBoostMultiple) {
      contexts::game_states::IncrementSpeed(registry_, kSpeedBoost);
    }
  }
}
