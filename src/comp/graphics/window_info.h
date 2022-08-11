/**
 * @file      window_info.h
 * @brief     Window information component
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-10
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_COMP_GRAPHICS_WINDOW_INFO_H_
#define ENTT_DINO_SRC_COMP_GRAPHICS_WINDOW_INFO_H_

#include <SDL2/SDL_rect.h>

namespace components {

namespace graphics {

struct WindowInfo {
  SDL_Rect bounds;
};

}  // namespace graphics

}  // namespace components

#endif  // ENTT_DINO_SRC_COMP_GRAPHICS_WINDOW_INFO_H_
