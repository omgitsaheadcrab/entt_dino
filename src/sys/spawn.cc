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
#include "ctx/general.h"
#include "ent/cloud.h"
#include "ent/floor.h"

void systems::spawn::Clouds(entt::registry* registry,
                            const ResourceManager& res_manager) {
  const auto spawner_view = registry->view<components::attributes::Spawner,
                                           components::entities::Cloud>();
  const auto bg_view =
      registry
          ->view<components::physics::Transform, components::entities::Cloud>();
  const auto& window = contexts::GetWindowInfo(registry);

  spawner_view.each([&](auto& spawner) {
    if (spawner.count == 0) {
      double pos = window.bounds.w / 4.0;
      entities::CreateCloud(registry, res_manager, pos);
      ++spawner.count;

      while (spawner.count < spawner.capacity) {
        pos += window.bounds.w / 2.0;
        entities::CreateCloud(registry, res_manager, pos);
        ++spawner.count;
      }
    }

    bg_view.each([&](auto entity, const auto& transform) {
      if (transform.position.x <= -transform.position.w) {
        registry->emplace<components::entity_states::Despawn>(entity);
        const auto pos = transform.position.x + transform.position.w +
                         (window.bounds.w / 2.0 * spawner.capacity);

        entities::CreateCloud(registry, res_manager, pos);
        ++spawner.count;
      }
    });
  });
}

void systems::spawn::Floors(entt::registry* registry,
                            const ResourceManager& res_manager) {
  const auto spawner_view = registry->view<components::attributes::Spawner,
                                           components::entities::Floor>();
  const auto bg_view =
      registry
          ->view<components::physics::Transform, components::entities::Floor>();

  double current_pos = 0;
  double width = 0;

  spawner_view.each([&](auto& spawner) {
    if (spawner.count == 0) {
      entities::CreateFloor(registry, res_manager, 0);
      ++spawner.count;
      bg_view.each([&](const auto& transform) {
        current_pos = transform.position.x + transform.position.w;
        width = transform.position.w;
      });

      while (spawner.count < spawner.capacity) {
        entities::CreateFloor(registry, res_manager, current_pos);
        ++spawner.count;
        current_pos += width;
      }
    }

    bg_view.each([&](auto entity, const auto& transform) {
      if (transform.position.x <= -transform.position.w) {
        registry->emplace<components::entity_states::Despawn>(entity);
        const auto pos =
            transform.position.x + (transform.position.w * spawner.capacity);

        entities::CreateFloor(registry, res_manager, pos);
        ++spawner.count;
      }
    });
  });
}
