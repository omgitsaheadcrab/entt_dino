/**
 * @file      res_manager.cc
 * @brief     Resource Manager
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2025-09-15
 * @copyright Copyright © 2025 Tobias Backer Dirks
 */

#include "core/res_manager.h"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
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

omg::ResourceManager::~ResourceManager() {
  for (const auto& kFont : fonts_) {
    for (auto& size : kFont.second) {
      delete size;
    }
  }
  for (const auto& kSound : sounds_) {
    Mix_FreeChunk(kSound.second);
  }
}

void omg::ResourceManager::Init(SDL_Renderer* renderer) {
  renderer_ = renderer;
  ParseSprites();
  LoadSprites();
  ParseFonts();
  LoadSounds();
}

void omg::ResourceManager::ParseSprites() {
  std::string sprite_dir = utils::GetResPath() + "sprites";
  for (const auto& kEntry : std::filesystem::directory_iterator(sprite_dir)) {
    if (kEntry.path().extension() == ".json") {
      nlohmann::json sprite;
      std::ifstream json_file(kEntry.path());
      json_file >> sprite;
      resources_["sprites"][kEntry.path().stem()]["frames"] = sprite["frames"];
      resources_["sprites"][kEntry.path().stem()]["slices"] =
          sprite["meta"]["slices"];
      nlohmann::json tags;
      for (auto tag : sprite["meta"]["frameTags"]) {
        const auto tag_name = tag["name"];
        tag.erase("name");
        tags[tag_name] = tag;
      }
      resources_["sprites"][kEntry.path().stem()]["frame_tags"] = tags;

      const auto kFilepath = kEntry.path().parent_path().string() + "/" +
                             sprite["meta"]["image"].get<std::string>();
      resources_["sprites"][kEntry.path().stem()]["filepath"] = kFilepath;
    }
  }
}

void omg::ResourceManager::LoadSprites() {
  for (const auto& [kKey, kSprite] : resources_["sprites"].items()) {
    SPDLOG_DEBUG("Loading sprite: {}", kKey);
    sprite_textures_[kKey] = graphics::LoadTexture(
        IMG_Load(kSprite["filepath"].get<std::string>().c_str()), renderer_);
  }
}

std::vector<SDL_Rect> omg::ResourceManager::GetSpriteClips(
    const std::string& kSprite, const std::string& kTag) const {
  const auto from = resources_["sprites"][kSprite]["frame_tags"][kTag]["from"];
  const auto to = resources_["sprites"][kSprite]["frame_tags"][kTag]["to"];

  std::vector<SDL_Rect> sprites;
  uint32_t iter = 0;
  for (const auto& kFrame : resources_["sprites"][kSprite]["frames"]) {
    if (iter >= from && iter <= to) {
      const SDL_Rect kClip {kFrame["frame"]["x"], kFrame["frame"]["y"],
                            kFrame["frame"]["w"], kFrame["frame"]["h"]};
      sprites.push_back(kClip);
    }
    ++iter;
  }
  return sprites;
}

std::vector<SDL_Rect> omg::ResourceManager::GetSpriteClipsFromSlices(
    const std::string& kSprite, const std::string& kTag) const {
  std::vector<SDL_Rect> sprites;
  for (const auto& kSlice : resources_["sprites"][kSprite]["slices"]) {
    if (kSlice["name"].get<std::string>().find(kTag) != std::string::npos) {
      const SDL_Rect kClip {
          kSlice["keys"][0]["bounds"]["x"], kSlice["keys"][0]["bounds"]["y"],
          kSlice["keys"][0]["bounds"]["w"], kSlice["keys"][0]["bounds"]["h"]};
      sprites.push_back(kClip);
    }
  }
  return sprites;
}

SDL_Texture* omg::ResourceManager::GetSpriteTexture(
    const std::string& kSpriteName) const {
  return sprite_textures_.find(kSpriteName)->second;
}

void omg::ResourceManager::ParseFonts() {
  const std::string kFontDir = utils::GetResPath() + "fonts";
  for (const auto& kEntry : std::filesystem::directory_iterator(kFontDir)) {
    if (kEntry.path().extension() == ".ttf") {
      const auto kFilepath = kEntry.path().parent_path().string();
      resources_["fonts"][kEntry.path().stem()]["filepath"] = kFilepath;
      resources_["fonts"][kEntry.path().stem()]["extension"] = ".ttf";
      const std::vector<fonts::Font*> kSizes;
      fonts_[kEntry.path().stem().string()] = kSizes;
    }
  }
}

void omg::ResourceManager::LoadFont(const std::string& kName,
                                    const uint32_t kSize) {
  fonts_[kName].resize(kSize + 1);
  SPDLOG_DEBUG("Loading font: {}:{}pt", kName, kSize);

  // TODO(omgitsaheadcrab): move to helper
  const std::string kFontPath =
      resources_["fonts"][kName]["filepath"].get<std::string>() + "/" + kName +
      resources_["fonts"][kName]["extension"].get<std::string>();

  const auto kFont = fonts::LoadFontCache(kName, kSize, kFontPath, renderer_);
  fonts_[kName][kSize] = kFont;
}

void omg::ResourceManager::DrawText(const std::string& kText,
                                    const SDL_Rect& kPosition,
                                    const SDL_Color& kColor,
                                    const std::string& kFontName,
                                    const uint32_t kFontSize) {
  int i, character;
  int x = kPosition.x;
  SDL_Rect *glyph, dest;

  if (fonts_[kFontName].size() <= kFontSize || !fonts_[kFontName][kFontSize]) {
    LoadFont(kFontName, kFontSize);
  }

  const auto kFont = fonts_[kFontName][kFontSize];
  SDL_SetTextureColorMod(kFont->texture, kColor.r, kColor.g, kColor.b);

  i = 0;
  character = kText[i++];

  while (character) {
    glyph = &kFont->glyphs[character];

    dest.x = x;
    dest.y = kPosition.y;
    dest.w = glyph->w;
    dest.h = glyph->h;

    SDL_RenderCopy(renderer_, kFont->texture, glyph, &dest);

    x += glyph->w;
    character = kText[i++];
  }
}

void omg::ResourceManager::LoadSounds() {
  const std::string kSoundDir = utils::GetResPath() + "sounds";
  for (const auto& kEntry : std::filesystem::directory_iterator(kSoundDir)) {
    if (kEntry.path().extension() == ".wav") {
      resources_["sounds"][kEntry.path().stem()]["filepath"] =
          kEntry.path().string();
      resources_["sounds"][kEntry.path().stem()]["extension"] = ".wav";
      sounds_[kEntry.path().stem().string()] =
          Mix_LoadWAV(kEntry.path().string().c_str());
      SPDLOG_DEBUG("Loading sound: {}", kEntry.path().stem().string());
    }
  }
}

Mix_Chunk* omg::ResourceManager::GetSound(const std::string& kSoundName) const {
  return sounds_.find(kSoundName)->second;
}

//  LocalWords:  LoadFonts
