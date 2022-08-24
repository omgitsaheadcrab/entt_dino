/**
 * @file      spawn.cc
 * @brief     Spawn system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-11-18
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */
#include "sys/spawn.h"

#include <entt/entity/registry.hpp>

#include "comp/entities/cloud.h"
#include "comp/entities/floor.h"
#include "comp/entity_states/despawn.h"
#include "comp/physics/transform.h"
#include "core/res_manager.h"
#include "ctx/graphics.h"
#include "ent/cloud.h"
#include "ent/floor.h"

void systems::spawn::Clouds(entt::registry* registry,
                            const omg::ResourceManager& kResManager) {
  const auto kCloudView =
      registry
          ->view<components::physics::Transform, components::entities::Cloud>();
  const auto& kBounds = contexts::graphics::GetBounds(registry);
  constexpr auto kMaxCount = 2;

  auto count = kCloudView.size_hint();

  if (count == 0) {
    double pos = kBounds.position.w / 4.0;
    entities::background::CreateCloud(registry, kResManager, pos);
    ++count;

    while (count < kMaxCount) {
      pos += kBounds.position.w / 2.0;
      entities::background::CreateCloud(registry, kResManager, pos);
      ++count;
    }
  }

  kCloudView.each([&](auto entity, const auto& kTransform) {
    if (kTransform.position.x <= -kTransform.position.w) {
      registry->emplace<components::entity_states::Despawn>(entity);
      const auto kPos = kTransform.position.x + kTransform.position.w +
                        (kBounds.position.w / 2.0 * kMaxCount);

      entities::background::CreateCloud(registry, kResManager, kPos);
      ++count;
    }
  });
}

void systems::spawn::Floors(entt::registry* registry,
                            const omg::ResourceManager& kResManager) {
  const auto kFloorView =
      registry
          ->view<components::physics::Transform, components::entities::Floor>();
  constexpr auto kMaxCount = 3;

  auto current_pos = 0;
  auto width = 0;
  auto count = kFloorView.size_hint();

  if (count == 0) {
    entities::background::CreateFloor(registry, kResManager, 0);
    ++count;
    kFloorView.each([&](const auto& kTransform) {
      current_pos = kTransform.position.x + kTransform.position.w;
      width = kTransform.position.w;
    });

    while (count < kMaxCount) {
      entities::background::CreateFloor(registry, kResManager, current_pos);
      ++count;
      current_pos += width;
    }
  }

  kFloorView.each([&](auto entity, const auto& kTransform) {
    if (kTransform.position.x <= -kTransform.position.w) {
      registry->emplace<components::entity_states::Despawn>(entity);
      const auto kPos =
          kTransform.position.x + (kTransform.position.w * kMaxCount);

      entities::background::CreateFloor(registry, kResManager, kPos);
    }
  });
}
