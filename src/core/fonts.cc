/**
 * @file      fonts.cc
 * @brief     Font utility functions
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-07-29
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#include "core/fonts.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>

#include <string>

#include "core/graphics.h"

fonts::Font* fonts::LoadFontCache(const std::string& name, const int size,
                                  const std::string& path,
                                  SDL_Renderer* renderer) {
  // Constants
  constexpr int MAX_GLYPHS = 128;
  constexpr int FONT_TEXTURE_SIZE = 512;
  constexpr SDL_Color white = {255, 255, 255};

  auto ttf_font = TTF_OpenFont(path.c_str(), size);
  auto surface = SDL_CreateRGBSurface(0, FONT_TEXTURE_SIZE, FONT_TEXTURE_SIZE,
                                      32, 0, 0, 0, 0xff);
  SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGBA(surface->format, 0, 0, 0, 0));
  std::vector<SDL_Rect> glyphs(MAX_GLYPHS, SDL_Rect());
  SDL_Surface* text;
  SDL_Rect dest;
  SDL_Rect* glyph;
  char character[2];

  dest.x = 0;
  dest.y = 0;

  for (auto i = ' '; i <= 'z'; i++) {
    character[0] = i;  // Set ASCII value
    character[1] = 0;  // Null terminate
    text = TTF_RenderUTF8_Blended(ttf_font, character, white);
    TTF_SizeText(ttf_font, character, &dest.w, &dest.h);

    if (dest.x + dest.w >= FONT_TEXTURE_SIZE) {
      dest.x = 0;
      dest.y += dest.h + 1;

      if (dest.y + dest.h >= FONT_TEXTURE_SIZE) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL,
                       "Out of glyph space in %dx%d font atlas texture map.",
                       FONT_TEXTURE_SIZE, FONT_TEXTURE_SIZE);
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
  auto font = new Font {name, size, texture, glyphs};
  return font;
}
