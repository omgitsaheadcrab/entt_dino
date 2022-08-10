/**
 * @file      rigid_body.h
 * @brief     Rigid body component
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-08
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_COMP_PHYSICS_RIGID_BODY_H_
#define ENTT_DINO_SRC_COMP_PHYSICS_RIGID_BODY_H_

#include "core/vec2d.h"

namespace components {

namespace physics {

struct RigidBody {
  vf2d velocity;
  vf2d acceleration;
};

}  // namespace physics

}  // namespace components

#endif  // ENTT_DINO_SRC_COMP_PHYSICS_RIGID_BODY_H_
