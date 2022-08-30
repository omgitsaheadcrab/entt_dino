/**
 * @file      score.cc
 * @brief     Scoring system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-22
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#include "sys/score.h"

#include "ctx/game_states.h"
#include "events/dino/dead.h"

void systems::Score::OnInit() {
  dispatcher_->sink<events::dino::Dead>()
      .connect<&systems::Score::UpdateHighscore>(this);

  contexts::game_states::SetSpeed(registry_, 0.15);
  contexts::game_states::SetScore(registry_, 0);
  contexts::game_states::SetHighscore(registry_, 0);
}

void systems::Score::Update(const double dt) {
  const auto kScore = contexts::game_states::GetScore(registry_).value;
  if (contexts::game_states::GetDistance(registry_).value / kDistanceScale_ >
      kScore) {
    contexts::game_states::IncrementScore(registry_, 1);

    // Integer division to detect threshold cross
    if (kScore / kSpeedBoostMultiple_ <
        contexts::game_states::GetScore(registry_).value /
            kSpeedBoostMultiple_) {
      contexts::game_states::IncrementSpeed(registry_, kSpeedBoost_);
    }
  }
}

void systems::Score::UpdateHighscore(const events::dino::Dead&) {
  const auto kScore = contexts::game_states::GetScore(registry_).value;
  auto high_score = contexts::game_states::GetHighscore(registry_).value;
  high_score = kScore > high_score ? kScore : high_score;
  contexts::game_states::SetHighscore(registry_, high_score);
}
