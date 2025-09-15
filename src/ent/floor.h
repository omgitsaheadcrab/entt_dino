/**
 * @file      floor.h
 * @brief     Floor entity
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2025-09-15
 * @copyright Copyright © 2025 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_ENT_FLOOR_H_
#define ENTT_DINO_SRC_ENT_FLOOR_H_

#include <entt/entity/registry.hpp>

#include "core/res_manager.h"

namespace entities {

namespace background {

void CreateFloor(entt::registry* registry,
                 const omg::ResourceManager& kResManager, const int kXPos);

}  // namespace background

}  // namespace entities

#endif  // ENTT_DINO_SRC_ENT_FLOOR_H_
