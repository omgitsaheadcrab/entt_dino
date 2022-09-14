/**
 * @file      spawn.cc
 * @brief     Spawn system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-11-18
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */
#include "sys/spawn.h"

#include "comp/entity/despawn.h"
#include "comp/identifiers/cloud.h"
#include "comp/identifiers/floor.h"
#include "comp/physics/transform.h"
#include "core/game.h"
#include "ctx/graphics.h"
#include "ent/cloud.h"
#include "ent/dino.h"
#include "ent/floor.h"

void systems::Spawn::OnInit() {
  entities::dino::Create(registry_, game_->res_manager());
  Clouds();
  Floors();
}

void systems::Spawn::Update(const double dt) {
  Clouds();
  Floors();
}

void systems::Spawn::Clouds() {
  const auto kCloudView = registry_->view<components::physics::Transform,
                                          components::identifiers::Cloud>();
  const auto& kBounds = contexts::graphics::GetBounds(registry_);
  constexpr auto kMaxCount = 2;

  auto count = kCloudView.size_hint();

  if (count == 0) {
    double pos = kBounds.position.w / 4.0;
    entities::background::CreateCloud(registry_, game_->res_manager(), pos);
    ++count;

    while (count < kMaxCount) {
      pos += kBounds.position.w / 2.0;
      entities::background::CreateCloud(registry_, game_->res_manager(), pos);
      ++count;
    }
  }

  kCloudView.each([&](auto entity, const auto& kTransform) {
    if (kTransform.position.x <= -kTransform.position.w) {
      registry_->emplace<components::entity::Despawn>(entity);
      const auto kPos = kTransform.position.x + kTransform.position.w +
                        (kBounds.position.w / 2.0 * kMaxCount);

      entities::background::CreateCloud(registry_, game_->res_manager(), kPos);
      ++count;
    }
  });
}

void systems::Spawn::Floors() {
  const auto kFloorView = registry_->view<components::physics::Transform,
                                          components::identifiers::Floor>();
  constexpr auto kMaxCount = 3;

  auto current_pos = 0;
  auto width = 0;
  auto count = kFloorView.size_hint();

  if (count == 0) {
    entities::background::CreateFloor(registry_, game_->res_manager(), 0);
    ++count;
    kFloorView.each([&](const auto& kTransform) {
      current_pos = kTransform.position.x + kTransform.position.w;
      width = kTransform.position.w;
    });

    while (count < kMaxCount) {
      entities::background::CreateFloor(registry_, game_->res_manager(),
                                        current_pos);
      ++count;
      current_pos += width;
    }
  }

  kFloorView.each([&](auto entity, const auto& kTransform) {
    if (kTransform.position.x <= -kTransform.position.w) {
      registry_->emplace<components::entity::Despawn>(entity);
      const auto kPos =
          kTransform.position.x + (kTransform.position.w * kMaxCount);

      entities::background::CreateFloor(registry_, game_->res_manager(), kPos);
    }
  });
}
