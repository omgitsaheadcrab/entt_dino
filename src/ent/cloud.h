/**
 * @file      cloud.h
 * @brief     Cloud entity
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-11-25
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_ENT_CLOUD_H_
#define ENTT_DINO_SRC_ENT_CLOUD_H_

#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>

#include "core/res_manager.h"

namespace entities {

entt::entity CreateCloud(entt::registry* registry,
                         const ResourceManager& res_manager, const int xpos);

}  // namespace entities

#endif  // ENTT_DINO_SRC_ENT_CLOUD_H_
