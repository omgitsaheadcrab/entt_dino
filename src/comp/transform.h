/**
 * @file      transform.h
 * @brief     Transform component
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-08
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_COMP_TRANSFORM_H_
#define ENTT_DINO_SRC_COMP_TRANSFORM_H_

#include <SDL2/SDL_rect.h>

#include "core/vec2d.h"

namespace components {

struct Transform {
  SDL_Rect* position;
  vf2d direction;
};

}  // namespace components

#endif  // ENTT_DINO_SRC_COMP_TRANSFORM_H_
