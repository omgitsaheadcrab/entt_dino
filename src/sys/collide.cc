/**
 * @file      collide.cc
 * @brief     Collide system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-24
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#include "sys/collide.h"

#include <SDL2/SDL_rect.h>
#include <spdlog/spdlog.h>

#include "comp/entity/states.h"
#include "comp/identifiers/dino.h"
#include "comp/physics/collider.h"
#include "comp/physics/transform.h"
#include "ctx/game_states.h"
#include "ent/dino.h"
#include "events/dino/running.h"

void systems::Collide::Update(const double dt) {
  const auto kView = registry_->view<components::physics::Transform,
                                     components::physics::Collider>();
  const auto kDinoView =
      registry_
          ->view<components::identifiers::Dino, components::physics::Transform,
                 components::physics::Collider>();

  kDinoView.each([&](const auto& kDinoEntity, auto& dino_transform,
                     const auto& kDinoCollider) {
    const SDL_Rect kDinoColliderPos {
        dino_transform.position.x + kDinoCollider.box.x,
        dino_transform.position.y + kDinoCollider.box.y, kDinoCollider.box.w,
        kDinoCollider.box.h};

    kView.each([&](const auto& kColliderEntity, const auto& kTransform,
                   const auto& kCollider) {
      if (kDinoEntity != kColliderEntity) {
        const SDL_Rect kColliderPos {kTransform.position.x + kCollider.box.x,
                                     kTransform.position.y + kCollider.box.y,
                                     kCollider.box.w, kCollider.box.h};
        SDL_Rect intersect;
        bool has_intersect =
            SDL_IntersectRect(&kDinoColliderPos, &kColliderPos, &intersect);
        if (has_intersect) {
          dino_transform.position.y -= intersect.h;
          dispatcher_->trigger<events::dino::Running>();
        }
      }
    });
  });
}
