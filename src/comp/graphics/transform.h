/**
 * @file      transform.h
 * @brief     Graphics transform component
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-08
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_COMP_GRAPHICS_TRANSFORM_H_
#define ENTT_DINO_SRC_COMP_GRAPHICS_TRANSFORM_H_

#include <SDL2/SDL_rect.h>

namespace components {

namespace graphics {

struct Transform {
  SDL_Rect position;
};

}  // namespace graphics

}  // namespace components

#endif  // ENTT_DINO_SRC_COMP_GRAPHICS_TRANSFORM_H_
