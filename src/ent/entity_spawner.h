/**
 * @file      entity_spawner.h
 * @brief     Entity spawner entity.
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-08
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_ENT_ENTITY_SPAWNER_H_
#define ENTT_DINO_SRC_ENT_ENTITY_SPAWNER_H_

#include <cstdint>

#include <entt/entity/registry.hpp>

namespace entities {

void CreateCloudSpawner(entt::registry* registry, const uint32_t kCapacity);

void CreateFloorSpawner(entt::registry* registry, const uint32_t kCapacity);

}  // namespace entities

#endif  // ENTT_DINO_SRC_ENT_ENTITY_SPAWNER_H_
