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
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

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
  std::vector<SDL_Rect> GetSpriteClips(const std::string sprite) const;
  void DrawText(const std::string text, int x, const int y,
                const SDL_Color color, const std::string font_name,
                const int font_size);

  std::unordered_map<std::string, std::vector<fonts::Font*>> fonts;
  std::unordered_map<std::string, SDL_Texture*> sprite_textures;

 private:
  void ParseSprites();
  void LoadSprites();
  void ParseFonts();
  void LoadFont(const std::string name, const int size);

  SDL_Renderer* renderer_;
  nlohmann::json resources_;
};

#endif  // ENTT_DINO_SRC_CORE_RES_MANAGER_H_
