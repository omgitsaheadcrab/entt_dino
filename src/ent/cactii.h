/**
 * @file      cactii.h
 * @brief     Cactii entity
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-11-25
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_ENT_CACTII_H_
#define ENTT_DINO_SRC_ENT_CACTII_H_

#include <entt/entity/registry.hpp>

#include "core/res_manager.h"

namespace entities {

namespace enemies {

void CreateCactii(entt::registry* registry,
                  const omg::ResourceManager& kResManager);

}  // namespace enemies

}  // namespace entities

#endif  // ENTT_DINO_SRC_ENT_CACTII_H_
