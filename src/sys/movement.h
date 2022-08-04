/**
 * @file      movement.h
 * @brief     Movement system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-24
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_SYS_MOVEMENT_H_
#define ENTT_DINO_SRC_SYS_MOVEMENT_H_

#include <cstdint>

#include <entt/entity/registry.hpp>

namespace systems {

void Move(entt::registry* registry, const uint32_t base_speed);

}  // namespace systems

#endif  // ENTT_DINO_SRC_SYS_MOVEMENT_H_
