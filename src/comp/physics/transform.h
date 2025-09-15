/**
 * @file      transform.h
 * @brief     Physics transform component
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2025-09-15
 * @copyright Copyright © 2025 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_COMP_PHYSICS_TRANSFORM_H_
#define ENTT_DINO_SRC_COMP_PHYSICS_TRANSFORM_H_

#include <SDL2/SDL_rect.h>

namespace components {

namespace physics {

struct Transform {
  SDL_Rect position;
};

}  // namespace physics

}  // namespace components

#endif  // ENTT_DINO_SRC_COMP_PHYSICS_TRANSFORM_H_
