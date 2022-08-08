/**
 * @file      spawner.h
 * @brief     Spawner entity
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-08
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_ENT_SPAWNER_H_
#define ENTT_DINO_SRC_ENT_SPAWNER_H_

#include <cstdint>

#include <entt/entity/registry.hpp>

#include "comp/tags.h"

namespace entities {

void CreateCloudSpawner(entt::registry* registry, const uint32_t capacity);

void CreateFloorSpawner(entt::registry* registry, const uint32_t capacity);

}  // namespace entities

#endif  // ENTT_DINO_SRC_ENT_SPAWNER_H_
