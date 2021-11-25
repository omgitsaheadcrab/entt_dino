/**
 * @file      despawn.h
 * @brief     Despawn system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-11-18
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_SYS_DESPAWN_H_
#define ENTT_DINO_SRC_SYS_DESPAWN_H_

#include <set>

#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>

namespace systems {

std::set<entt::entity> Despawn(entt::registry* registry);

}  // namespace systems

#endif  // ENTT_DINO_SRC_SYS_DESPAWN_H_
