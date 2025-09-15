/**
 * @file      move.cc
 * @brief     Move system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2025-09-15
 * @copyright Copyright © 2025 Tobias Backer Dirks
 */

#include "sys/move.h"

#include "comp/physics/rigid_body.h"
#include "comp/physics/transform.h"
#include "ctx/game_states.h"

void systems::Move::Update(const double dt) {
  const auto kView = registry_->view<components::physics::Transform,
                                     components::physics::RigidBody>();
  const auto kBaseSpeed = contexts::game::GetSpeed(registry_);

  kView.each([&](auto& transform, const auto& kRigidBody) {
    // Need to round up to ensure sub pixel moves progress
    transform.position.x +=
        std::ceil(kRigidBody.velocity.x * dt * kBaseSpeed.value);
    transform.position.y +=
        kRigidBody.velocity.y * dt + 0.5 * kRigidBody.acceleration.y * dt * dt;
  });
}
