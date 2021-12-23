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
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
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
  ParseSprites();
  LoadSprites(renderer);
}

void ResourceManager::ParseSprites() {
  std::string sprite_dir = utils::GetResPath() + "sprites";
  for (const auto& entry : std::filesystem::directory_iterator(sprite_dir)) {
    if (entry.path().extension() == ".json") {
      nlohmann::json sprite;
      std::ifstream json_file(entry.path());
      json_file >> sprite;

      resources["sprites"][entry.path().stem()]["frames"] = sprite["frames"];
      std::string filepath = entry.path().parent_path().string() + "/" +
                             sprite["meta"]["image"].get<std::string>();
      resources["sprites"][entry.path().stem()]["filepath"] = filepath;
    }
  }
}

void ResourceManager::LoadSprites(SDL_Renderer* renderer) {
  for (auto& [key, sprite] : resources["sprites"].items()) {
    SPDLOG_DEBUG("Loading: {}", key);
    sprite_textures[key] = graphics::LoadTexture(
        IMG_Load(sprite["filepath"].get<std::string>().c_str()), renderer);
  }
}

std::vector<SDL_Rect> ResourceManager::GetSpriteClips(
    const std::string sprite) const {
  std::vector<SDL_Rect> sprites;

  for (auto& frame : resources["sprites"][sprite]["frames"]) {
    SDL_Rect clip {frame["frame"]["x"], frame["frame"]["y"],
                   frame["frame"]["w"], frame["frame"]["h"]};
    sprites.push_back(clip);
  }

  return sprites;
}
