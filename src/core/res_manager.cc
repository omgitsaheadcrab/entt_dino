/**
 * @file      res_manager.cc
 * @brief     Resource Manager
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-12-22
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#include "core/res_manager.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <spdlog/spdlog.h>

#include <filesystem>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

#include <nlohmann/json.hpp>

#include "core/graphics.h"
#include "util/res.h"

void ResourceManager::Init(SDL_Renderer* renderer) {
  renderer_ = renderer;
  ParseSprites();
  LoadSprites();
  ParseFonts();
  LoadFonts();
}

void ResourceManager::ParseSprites() {
  std::string sprite_dir = utils::GetResPath() + "sprites";
  for (const auto& entry : std::filesystem::directory_iterator(sprite_dir)) {
    if (entry.path().extension() == ".json") {
      nlohmann::json sprite;
      std::ifstream json_file(entry.path());
      json_file >> sprite;

      resources_["sprites"][entry.path().stem()]["frames"] = sprite["frames"];
      std::string filepath = entry.path().parent_path().string() + "/" +
                             sprite["meta"]["image"].get<std::string>();
      resources_["sprites"][entry.path().stem()]["filepath"] = filepath;
    }
  }
}

void ResourceManager::LoadSprites() {
  for (auto& [key, sprite] : resources_["sprites"].items()) {
    SPDLOG_DEBUG("Loading sprite: {}", key);
    sprite_textures[key] = graphics::LoadTexture(
        IMG_Load(sprite["filepath"].get<std::string>().c_str()), renderer_);
  }
}

std::vector<SDL_Rect> ResourceManager::GetSpriteClips(
    const std::string sprite) const {
  std::vector<SDL_Rect> sprites;

  for (auto& frame : resources_["sprites"][sprite]["frames"]) {
    SDL_Rect clip {frame["frame"]["x"], frame["frame"]["y"],
                   frame["frame"]["w"], frame["frame"]["h"]};
    sprites.push_back(clip);
  }

  return sprites;
}

void ResourceManager::ParseFonts() {
  std::string font_dir = utils::GetResPath() + "fonts";
  for (const auto& entry : std::filesystem::directory_iterator(font_dir)) {
    if (entry.path().extension() == ".ttf") {
      std::string filepath = entry.path().parent_path().string();
      resources_["fonts"][entry.path().stem()]["name"] =
          entry.path().stem().string();
      resources_["fonts"][entry.path().stem()]["filepath"] = filepath;
    }
  }
}

void ResourceManager::LoadFonts() {
  int max_glyphs = 128;
  int font_size = 8;
  for (auto& font : resources_["fonts"]) {
    SPDLOG_DEBUG("Loading font: {}", font["name"]);
    std::vector<SDL_Rect> glyphs(max_glyphs, SDL_Rect());

    TTF_Font* ttf_font =
        TTF_OpenFont(font["filepath"].get<std::string>().c_str(), font_size);
    int FONT_TEXTURE_SIZE = 512;
    SDL_Surface* surface = SDL_CreateRGBSurface(
        0, FONT_TEXTURE_SIZE, FONT_TEXTURE_SIZE, 32, 0, 0, 0, 0xff);
    SDL_SetColorKey(surface, SDL_TRUE,
                    SDL_MapRGBA(surface->format, 0, 0, 0, 0));
    SDL_Surface* text;
    SDL_Rect dest;
    SDL_Rect* g;
    char c[2];
    dest.x = 0;
    dest.y = 0;
    SDL_Color white = {255, 255, 255};

    for (auto i = ' '; i <= 'z'; i++) {
      c[0] = i;
      c[1] = 0;
      text = TTF_RenderUTF8_Blended(ttf_font, c, white);
      TTF_SizeText(ttf_font, c, &dest.w, &dest.h);

      if (dest.x + dest.w >= FONT_TEXTURE_SIZE) {
        dest.x = 0;

        dest.y += dest.h + 1;

        if (dest.y + dest.h >= FONT_TEXTURE_SIZE) {
          SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                         SDL_LOG_PRIORITY_CRITICAL,
                         "Out of glyph space in %dx%d font atlas texture map.",
                         FONT_TEXTURE_SIZE, FONT_TEXTURE_SIZE);
          exit(1);
        }
      }

      SDL_BlitSurface(text, NULL, surface, &dest);

      g = &glyphs[i];

      g->x = dest.x;
      g->y = dest.y;
      g->w = dest.w;
      g->h = dest.h;

      SDL_FreeSurface(text);

      dest.x += dest.w;
    }
    font_textures[font["name"]] = graphics::LoadTexture(surface, renderer_);
    TTF_CloseFont(ttf_font);
  }
}

//  LocalWords:  LoadFonts
