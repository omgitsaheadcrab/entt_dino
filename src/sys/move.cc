/**
 * @file      move.cc
 * @brief     Move system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-24
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#include "sys/move.h"

#include <cmath>

#include "comp/entity/states.h"
#include "comp/identifiers/dino.h"
#include "comp/physics/rigid_body.h"
#include "comp/physics/transform.h"
#include "ctx/game_states.h"
#include "ent/dino.h"

void systems::Move::Update(const double dt) {
  const auto kView = registry_->view<components::physics::Transform,
                                     components::physics::RigidBody>();
  const auto kDinoDead =
      registry_
          ->view<components::identifiers::Dino, components::entity::State>();

  // Check if dino is dead, if he is do nothing
  if (entities::dino::IsCurrentState(registry_, States::dead)) {
    return;
  }

  const auto kBaseSpeed = contexts::game::GetSpeed(registry_);
  kView.each([&](auto& transform, const auto& kRigidBody) {
    // Need to round up to ensure sub pixel moves progress
    transform.position.x +=
        std::ceil(kRigidBody.velocity.x * dt * kBaseSpeed.value);
    transform.position.y +=
        kRigidBody.velocity.y * dt + 0.5 * kRigidBody.acceleration.y * dt * dt;
  });

  // Update game distance traveled
  contexts::game::IncrementDistance(registry_,
                                    std::ceil(dt * kBaseSpeed.value));
}
