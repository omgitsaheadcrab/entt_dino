/**
 * @file      graphics.h
 * @brief     Graphics utility functions
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-09
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_CORE_GRAPHICS_H_
#define ENTT_DINO_SRC_CORE_GRAPHICS_H_

#include <SDL2/SDL_render.h>

#include <memory>

namespace graphics {

SDL_Texture* LoadTexture(const std::shared_ptr<char[]> path,
                         SDL_Renderer* renderer);

}  // namespace graphics

#endif  // ENTT_DINO_SRC_CORE_GRAPHICS_H_
