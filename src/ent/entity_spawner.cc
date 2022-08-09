/**
 * @file      entity_spawner.cc
 * @brief     Entity spawner entity.
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-08
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#include "ent/entity_spawner.h"

#include <cstdint>

#include "comp/spawner.h"
#include "comp/tags.h"

void entities::CreateCloudSpawner(entt::registry* registry,
                                  const uint32_t capacity) {
  auto e = registry->create();
  registry->emplace<components::entity_tags::Cloud>(e);
  registry->emplace<components::Spawner>(e, capacity);
}

void entities::CreateFloorSpawner(entt::registry* registry,
                                  const uint32_t capacity) {
  auto e = registry->create();
  registry->emplace<components::entity_tags::Floor>(e);
  registry->emplace<components::Spawner>(e, capacity);
}
