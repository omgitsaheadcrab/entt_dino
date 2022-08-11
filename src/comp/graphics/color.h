/**
 * @file      color.h
 * @brief     Color component
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-11
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_COMP_GRAPHICS_COLOR_H_
#define ENTT_DINO_SRC_COMP_GRAPHICS_COLOR_H_

#include <SDL2/SDL_pixels.h>

namespace components {

namespace graphics {

struct Color {
  SDL_Color rgba;
};

}  // namespace graphics

}  // namespace components

#endif  // ENTT_DINO_SRC_COMP_GRAPHICS_COLOR_H_
