/**
 * @file      gravity.h
 * @brief     Gravity component
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2025-09-15
 * @copyright Copyright © 2025 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_COMP_PHYSICS_GRAVITY_H_
#define ENTT_DINO_SRC_COMP_PHYSICS_GRAVITY_H_

#include "core/vec2d.h"

namespace components {

namespace physics {

struct Gravity {
  vf2d force;
};

}  // namespace physics

}  // namespace components

#endif  // ENTT_DINO_SRC_COMP_PHYSICS_GRAVITY_H_
