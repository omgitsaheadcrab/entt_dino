/**
 * @file      bounds.h
 * @brief     Window bounds component
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2025-09-15
 * @copyright Copyright © 2025 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_COMP_GRAPHICS_BOUNDS_H_
#define ENTT_DINO_SRC_COMP_GRAPHICS_BOUNDS_H_

#include <SDL2/SDL_rect.h>

namespace components {

namespace graphics {

struct Bounds {
  SDL_Rect position;
};

}  // namespace graphics

}  // namespace components

#endif  // ENTT_DINO_SRC_COMP_GRAPHICS_BOUNDS_H_
