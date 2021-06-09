/**
 * @file      graphics.h
 * @brief     Graphics utility functions
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-09
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_CORE_GRAPHICS_H_
#define ENTT_DINO_SRC_CORE_GRAPHICS_H_

#include <SDL2/SDL_image.h>

#include <string>

SDL_Texture* LoadTexture(std::string path, SDL_Renderer* renderer);

#endif /* ENTT_DINO_SRC_CORE_GRAPHICS_H_ */
