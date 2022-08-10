/**
 * @file      entity_spawner.cc
 * @brief     Entity spawner entity.
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-08
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#include "ent/entity_spawner.h"

#include <cstdint>

#include "comp/attributes/spawner.h"
#include "comp/entities/cloud.h"
#include "comp/entities/floor.h"

void entities::CreateCloudSpawner(entt::registry* registry,
                                  const uint32_t capacity) {
  auto e = registry->create();
  registry->emplace<components::entities::Cloud>(e);
  registry->emplace<components::attributes::Spawner>(e, capacity);
}

void entities::CreateFloorSpawner(entt::registry* registry,
                                  const uint32_t capacity) {
  auto e = registry->create();
  registry->emplace<components::entities::Floor>(e);
  registry->emplace<components::attributes::Spawner>(e, capacity);
}
