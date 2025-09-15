/**
 * @file      sprite.h
 * @brief     Sprite component
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2025-09-15
 * @copyright Copyright © 2025 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_COMP_GRAPHICS_SPRITE_H_
#define ENTT_DINO_SRC_COMP_GRAPHICS_SPRITE_H_

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

namespace components {

namespace graphics {

struct Sprite {
  SDL_Texture* sheet;
  SDL_Rect clip;
};

}  // namespace graphics

}  // namespace components

#endif  // ENTT_DINO_SRC_COMP_GRAPHICS_SPRITE_H_
