/**
 * @file      colors.h
 * @brief     Common game colors
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-15
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_CORE_COLORS_H_
#define ENTT_DINO_SRC_CORE_COLORS_H_

#include <SDL2/SDL_pixels.h>

namespace colors {

constexpr SDL_Color kDinoGrey = {89, 86, 82};
constexpr SDL_Color kWhite = {255, 255, 255};

}  // namespace colors

#endif  // ENTT_DINO_SRC_CORE_COLORS_H_
