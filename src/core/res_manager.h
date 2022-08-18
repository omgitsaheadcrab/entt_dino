/**
 * @file      res_manager.h
 * @brief     Resource Manager
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-12-22
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_CORE_RES_MANAGER_H_
#define ENTT_DINO_SRC_CORE_RES_MANAGER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#include <nlohmann/json.hpp>

#include "core/fonts.h"

class ResourceManager {
 public:
  ResourceManager() = default;
  ~ResourceManager();

  void Init(SDL_Renderer* renderer);
  std::vector<SDL_Rect> GetSpriteClips(const std::string& kSprite) const;
  SDL_Texture* GetSpriteTexture(const std::string& kSpriteName) const;
  void DrawText(const std::string& kText, const SDL_Rect& kPositon,
                const SDL_Color& kColor, const std::string& kFontName,
                const u_int32_t kFontSize);

 private:
  void ParseSprites();
  void LoadSprites();
  void ParseFonts();
  void LoadFont(const std::string& kName, const uint32_t kSize);

  SDL_Renderer* renderer_;
  nlohmann::json resources_;
  std::unordered_map<std::string, std::vector<fonts::Font*>> fonts_;
  std::unordered_map<std::string, SDL_Texture*> sprite_textures_;
};

#endif  // ENTT_DINO_SRC_CORE_RES_MANAGER_H_
