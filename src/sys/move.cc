/**
 * @file      move.cc
 * @brief     Move system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-24
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#include "sys/move.h"

#include <cmath>

#include "comp/entities/dino.h"
#include "comp/entity_states/action.h"
#include "comp/physics/rigid_body.h"
#include "comp/physics/transform.h"
#include "ctx/game_states.h"
#include "ent/dino.h"

void systems::Move::Update(const double dt) {
  const auto kView = registry_->view<components::physics::Transform,
                                     components::physics::RigidBody>();
  const auto kDinoDead = registry_->view<components::entities::Dino,
                                         components::entity_states::Action>();

  // Check if dino is dead, if he is do nothing
  if (entities::dino::IsCurrentAction(registry_, Actions::dead)) {
    return;
  }

  const auto kBaseSpeed = contexts::game_states::GetSpeed(registry_);
  kView.each([&](auto& transform, const auto& kRigidBody) {
    // Need to round up to ensure sub pixel moves progress
    transform.position.x +=
        std::ceil(kRigidBody.velocity.x * dt * kBaseSpeed.value);
  });

  // Update game distance traveled
  contexts::game_states::IncrementDistance(registry_,
                                           std::ceil(dt * kBaseSpeed.value));
}
