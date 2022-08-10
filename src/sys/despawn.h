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

#include <entt/entity/registry.hpp>

namespace systems {

namespace despawn {

void OutOfBounds(entt::registry* registry);

}  // namespace despawn

}  // namespace systems

#endif  // ENTT_DINO_SRC_SYS_DESPAWN_H_
