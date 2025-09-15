/**
 * @file      dino.h
 * @brief     Dino entity
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2025-09-15
 * @copyright Copyright © 2025 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_ENT_DINO_H_
#define ENTT_DINO_SRC_ENT_DINO_H_

#include <entt/entity/registry.hpp>

#include "core/res_manager.h"

namespace entities {

namespace dino {

void Create(entt::registry* registry, const omg::ResourceManager& kResManager);

}  // namespace dino

}  // namespace entities

#endif  // ENTT_DINO_SRC_ENT_DINO_H_
