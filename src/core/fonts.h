/**
 * @file      fonts.h
 * @brief     Font utility functions
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2025-09-15
 * @copyright Copyright © 2025 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_CORE_FONTS_H_
#define ENTT_DINO_SRC_CORE_FONTS_H_

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

#include <cstdint>
#include <string>
#include <vector>

namespace fonts {

struct Font {
  std::string name;
  uint32_t size;
  SDL_Texture* texture;
  std::vector<SDL_Rect> glyphs;
};

Font* LoadFontCache(const std::string& kName, const uint32_t kSize,
                    const std::string& kPath, SDL_Renderer* renderer);

}  // namespace fonts

#endif  // ENTT_DINO_SRC_CORE_FONTS_H_
