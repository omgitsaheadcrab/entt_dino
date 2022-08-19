/**
 * @file      spawn.cc
 * @brief     Spawn system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-11-18
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */
#include "sys/spawn.h"

#include <entt/entity/registry.hpp>

#include "comp/attributes/spawner.h"
#include "comp/entities/cloud.h"
#include "comp/entities/floor.h"
#include "comp/entity_states/despawn.h"
#include "comp/physics/transform.h"
#include "core/res_manager.h"
#include "ctx/graphics.h"
#include "ent/cloud.h"
#include "ent/floor.h"

void systems::spawn::Clouds(entt::registry* registry,
                            const ResourceManager& kResManager) {
  const auto kSpawnerView = registry->view<components::attributes::Spawner,
                                           components::entities::Cloud>();
  const auto kCloudView =
      registry
          ->view<components::physics::Transform, components::entities::Cloud>();
  const auto& kBounds = contexts::graphics::GetBounds(registry);

  kSpawnerView.each([&](auto& spawner) {
    if (spawner.count == 0) {
      double pos = kBounds.position.w / 4.0;
      entities::background::CreateCloud(registry, kResManager, pos);
      ++spawner.count;

      while (spawner.count < spawner.capacity) {
        pos += kBounds.position.w / 2.0;
        entities::background::CreateCloud(registry, kResManager, pos);
        ++spawner.count;
      }
    }

    kCloudView.each([&](auto entity, const auto& kTransform) {
      if (kTransform.position.x <= -kTransform.position.w) {
        registry->emplace<components::entity_states::Despawn>(entity);
        const auto kPos = kTransform.position.x + kTransform.position.w +
                          (kBounds.position.w / 2.0 * spawner.capacity);

        entities::background::CreateCloud(registry, kResManager, kPos);
        ++spawner.count;
      }
    });
  });
}

void systems::spawn::Floors(entt::registry* registry,
                            const ResourceManager& kResManager) {
  const auto kSpawnerView = registry->view<components::attributes::Spawner,
                                           components::entities::Floor>();
  const auto kFloorView =
      registry
          ->view<components::physics::Transform, components::entities::Floor>();

  double current_pos = 0;
  double width = 0;

  kSpawnerView.each([&](auto& spawner) {
    if (spawner.count == 0) {
      entities::background::CreateFloor(registry, kResManager, 0);
      ++spawner.count;
      kFloorView.each([&](const auto& kTransform) {
        current_pos = kTransform.position.x + kTransform.position.w;
        width = kTransform.position.w;
      });

      while (spawner.count < spawner.capacity) {
        entities::background::CreateFloor(registry, kResManager, current_pos);
        ++spawner.count;
        current_pos += width;
      }
    }

    kFloorView.each([&](auto entity, const auto& kTransform) {
      if (kTransform.position.x <= -kTransform.position.w) {
        registry->emplace<components::entity_states::Despawn>(entity);
        const auto kPos =
            kTransform.position.x + (kTransform.position.w * spawner.capacity);

        entities::background::CreateFloor(registry, kResManager, kPos);
        ++spawner.count;
      }
    });
  });
}
