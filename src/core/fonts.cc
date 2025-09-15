/**
 * @file      fonts.cc
 * @brief     Font utility functions
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2025-07-29
 * @copyright Copyright © 2025 Tobias Backer Dirks
 */

#include "core/fonts.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>

#include <cstdint>
#include <string>
#include <vector>

#include "core/colors.h"
#include "core/graphics.h"

fonts::Font* fonts::LoadFontCache(const std::string& kName,
                                  const uint32_t kSize,
                                  const std::string& kPath,
                                  SDL_Renderer* renderer) {
  // Constants
  constexpr int kMaxGlyphs = 128;
  constexpr int kFontTextureSize = 512;

  auto ttf_font = TTF_OpenFont(kPath.c_str(), kSize);
  auto surface = SDL_CreateRGBSurface(0, kFontTextureSize, kFontTextureSize, 32,
                                      0, 0, 0, 0xff);
  SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGBA(surface->format, 0, 0, 0, 0));
  std::vector<SDL_Rect> glyphs(kMaxGlyphs, SDL_Rect());
  SDL_Surface* text;
  SDL_Rect dest;
  SDL_Rect* glyph;
  char character[2];

  dest.x = 0;
  dest.y = 0;

  for (auto i = ' '; i <= 'z'; i++) {
    character[0] = i;  // Set ASCII value
    character[1] = 0;  // Null terminate
    text = TTF_RenderUTF8_Blended(ttf_font, character, colors::kWhite);
    TTF_SizeText(ttf_font, character, &dest.w, &dest.h);

    if (dest.x + dest.w >= kFontTextureSize) {
      dest.x = 0;
      dest.y += dest.h + 1;

      if (dest.y + dest.h >= kFontTextureSize) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL,
                       "Out of glyph space in %dx%d font atlas texture map.",
                       kFontTextureSize, kFontTextureSize);
        exit(1);
      }
    }

    SDL_BlitSurface(text, NULL, surface, &dest);

    glyph = &glyphs[i];
    glyph->x = dest.x;
    glyph->y = dest.y;
    glyph->w = dest.w;
    glyph->h = dest.h;

    dest.x += dest.w;
    SDL_FreeSurface(text);
  }
  TTF_CloseFont(ttf_font);

  auto texture = graphics::LoadTexture(surface, renderer);
  auto font = new Font {kName, kSize, texture, glyphs};
  return font;
}
