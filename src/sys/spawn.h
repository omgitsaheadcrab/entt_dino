/**
 * @file      spawn.h
 * @brief     Spawn system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-11-18
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_SYS_SPAWN_H_
#define ENTT_DINO_SRC_SYS_SPAWN_H_

#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>

#include "core/res_manager.h"

namespace systems {

namespace spawn {

void Clouds(entt::registry* registry, const omg::ResourceManager& kResManager);

void Floors(entt::registry* registry, const omg::ResourceManager& kResManager);

}  // namespace spawn

}  // namespace systems

#endif  // ENTT_DINO_SRC_SYS_SPAWN_H_
