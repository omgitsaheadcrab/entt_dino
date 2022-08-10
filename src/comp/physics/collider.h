/**
 * @file      collider.h
 * @brief     Collider component
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-08
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_COMP_PHYSICS_COLLIDER_H_
#define ENTT_DINO_SRC_COMP_PHYSICS_COLLIDER_H_

#include "core/vec2d.h"

namespace components {

namespace physics {

struct Collider {
  vf2d size;
};

}  // namespace physics

}  // namespace components

#endif  // ENTT_DINO_SRC_COMP_PHYSICS_COLLIDER_H_
