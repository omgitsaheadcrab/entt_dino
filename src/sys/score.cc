/**
 * @file      score.cc
 * @brief     Scoring system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-22
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#include "sys/score.h"

#include <cmath>

#include "ctx/game_states.h"
#include "events/dino/dead.h"
#include "events/game/restart.h"

void systems::Score::OnInit() {
  dispatcher_->sink<events::game::Restart>()
      .connect<&systems::Score::OnRestart>(this);
  dispatcher_->sink<events::dino::Dead>().connect<&systems::Score::OnDead>(
      this);

  contexts::game::SetHighscore(registry_, 0);
  contexts::game::SetScore(registry_, 0);
  contexts::game::SetSpeed(registry_, 0.15);
  distance_ = 0;
  highscore_ = 0;
  score_ = 0;
  speed_ = 0.15;
}

void systems::Score::Update(const double dt) {
  distance_ += std::ceil(dt * speed_);

  if (distance_ / kDistanceScale_ > score_) {
    score_ += 1;
    contexts::game::SetScore(registry_, score_);

    // Integer division to detect threshold cross
    if (score_ / kSpeedBoostMultiple_ < score_ / kSpeedBoostMultiple_) {
      speed_ += kSpeedBoost_;
      contexts::game::SetSpeed(registry_, speed_);
    }
  }
}

void systems::Score::OnRestart() {
  contexts::game::SetScore(registry_, 0);
  contexts::game::SetSpeed(registry_, 0.15);
  distance_ = 0;
  score_ = 0;
  speed_ = 0.15;
}

void systems::Score::OnDead() {
  contexts::game::SetSpeed(registry_, 0);
  speed_ = 0;

  highscore_ = score_ > highscore_ ? score_ : highscore_;
  contexts::game::SetHighscore(registry_, highscore_);
}
