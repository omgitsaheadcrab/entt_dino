/**
 * @file      res_manager.cc
 * @brief     Resource Manager
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-12-22
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#include "core/res_manager.h"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <spdlog/spdlog.h>

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

#include <nlohmann/json.hpp>

#include "core/fonts.h"
#include "core/graphics.h"
#include "util/res.h"

ResourceManager::~ResourceManager() {
  for (const auto& font : fonts) {
    for (const auto& size : font.second) {
      delete size;
    }
  }
}

void ResourceManager::Init(SDL_Renderer* renderer) {
  renderer_ = renderer;
  ParseSprites();
  LoadSprites();
  ParseFonts();
}

void ResourceManager::ParseSprites() {
  std::string sprite_dir = utils::GetResPath() + "sprites";
  for (const auto& entry : std::filesystem::directory_iterator(sprite_dir)) {
    if (entry.path().extension() == ".json") {
      nlohmann::json sprite;
      std::ifstream json_file(entry.path());
      json_file >> sprite;

      resources_["sprites"][entry.path().stem()]["frames"] = sprite["frames"];
      auto filepath = entry.path().parent_path().string() + "/" +
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
    const std::string& sprite) const {
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
      auto filepath = entry.path().parent_path().string();
      resources_["fonts"][entry.path().stem()]["filepath"] = filepath;
      resources_["fonts"][entry.path().stem()]["extension"] = ".ttf";
      std::vector<fonts::Font*> sizes;
      fonts[entry.path().stem().string()] = sizes;
    }
  }
}

void ResourceManager::LoadFont(const std::string& name, const uint32_t size) {
  fonts[name].resize(size + 1);
  SPDLOG_DEBUG("Loading font: {}:{}pt", name, size);

  // TODO(omgitsaheadcrab): move to helper
  const std::string font_path =
      resources_["fonts"][name]["filepath"].get<std::string>() + "/" + name +
      resources_["fonts"][name]["extension"].get<std::string>();

  auto font = fonts::LoadFontCache(name, size, font_path, renderer_);
  fonts[name][size] = font;
}

void ResourceManager::DrawText(const std::string& text, uint32_t x,
                               const uint32_t y, const SDL_Color& color,
                               const std::string& font_name,
                               const uint32_t font_size) {
  int i, character;
  SDL_Rect *glyph, dest;

  if (fonts[font_name].size() <= font_size || !fonts[font_name][font_size]) {
    LoadFont(font_name, font_size);
  }

  auto font = fonts[font_name][font_size];
  SDL_SetTextureColorMod(font->texture, color.r, color.g, color.b);

  i = 0;
  character = text[i++];

  while (character) {
    glyph = &font->glyphs[character];

    dest.x = x;
    dest.y = y;
    dest.w = glyph->w;
    dest.h = glyph->h;

    SDL_RenderCopy(renderer_, font->texture, glyph, &dest);

    x += glyph->w;
    character = text[i++];
  }
}

//  LocalWords:  LoadFonts
