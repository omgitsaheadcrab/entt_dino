/**
 * @file      sprite.h
 * @brief     Sprite component
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-08
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_COMP_SPRITE_H_
#define ENTT_DINO_SRC_COMP_SPRITE_H_

#include <SDL2/SDL_render.h>

#include "core/vec2d.h"

namespace components {

struct Sprite {
  SDL_Texture* sheet;
  vf2d position;
  vf2d size;
};

}  // namespace components

#endif  // ENTT_DINO_SRC_COMP_SPRITE_H_
