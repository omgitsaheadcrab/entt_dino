/**
 * @file      collide.cc
 * @brief     Collide system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2025-06-24
 * @copyright Copyright © 2025 Tobias Backer Dirks
 */

#include "sys/collide.h"

#include <SDL2/SDL_rect.h>
#include <spdlog/spdlog.h>

#include "comp/identifiers/dino.h"
#include "comp/identifiers/enemy.h"
#include "comp/identifiers/floor.h"
#include "comp/physics/collider.h"
#include "comp/physics/transform.h"
#include "events/dino/dead.h"
#include "events/dino/running.h"

void systems::Collide::Update(const double dt) {
  if (EnemyCollision()) {
    dispatcher_->trigger<events::dino::Dead>();
  } else {
    Resolve();
  }
}

void systems::Collide::Resolve() {
  const auto kView =
      registry_
          ->view<components::identifiers::Floor, components::physics::Transform,
                 components::physics::Collider>();
  const auto kDinoView =
      registry_
          ->view<components::identifiers::Dino, components::physics::Transform,
                 components::physics::Collider>();

  kDinoView.each([&](auto& dino_transform, const auto& kDinoCollider) {
    const SDL_Rect kDinoColliderPos {
        dino_transform.position.x + kDinoCollider.box.x,
        dino_transform.position.y + kDinoCollider.box.y, kDinoCollider.box.w,
        kDinoCollider.box.h};
    kView.each([&](const auto& kTransform, const auto& kCollider) {
      const SDL_Rect kColliderPos {kTransform.position.x + kCollider.box.x,
                                   kTransform.position.y + kCollider.box.y,
                                   kCollider.box.w, kCollider.box.h};
      SDL_Rect intersect;
      bool has_intersect =
          SDL_IntersectRect(&kDinoColliderPos, &kColliderPos, &intersect);
      if (has_intersect) {
        SPDLOG_DEBUG("Floor collision detected! {}", intersect.h);
        dino_transform.position.y -= intersect.h;
        dispatcher_->trigger<events::dino::Running>();
        return;
      }
    });
  });
}

bool systems::Collide::EnemyCollision() {
  bool has_intersect = false;
  const auto kEnemyView =
      registry_
          ->view<components::identifiers::Enemy, components::physics::Transform,
                 components::physics::Collider>();
  const auto kDinoView =
      registry_
          ->view<components::identifiers::Dino, components::physics::Transform,
                 components::physics::Collider>();

  kDinoView.each([&](auto& dino_transform, const auto& kDinoCollider) {
    const SDL_Rect kDinoColliderPos {
        dino_transform.position.x + kDinoCollider.box.x,
        dino_transform.position.y + kDinoCollider.box.y, kDinoCollider.box.w,
        kDinoCollider.box.h};

    kEnemyView.each([&](const auto& ent, const auto& kTransform,
                        const auto& kEnemyCollider) {
      const SDL_Rect kEnemyPos {kTransform.position.x + kEnemyCollider.box.x,
                                kTransform.position.y + kEnemyCollider.box.y,
                                kEnemyCollider.box.w, kEnemyCollider.box.h};
      SDL_Rect intersect;
      bool intersected =
          SDL_IntersectRect(&kDinoColliderPos, &kEnemyPos, &intersect);
      if (intersected) has_intersect = true;
    });
  });
  return has_intersect;
}
