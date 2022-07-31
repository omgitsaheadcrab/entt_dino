/**
 * @file      hud.h
 * @brief     Game HUD
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-07-26
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_CORE_HUD_H_
#define ENTT_DINO_SRC_CORE_HUD_H_

#include <SDL2/SDL_image.h>

#include <string>

#include "SDL_rect.h"
#include "SDL_render.h"
#include "core/res_manager.h"
#include "core/window.h"

struct Element {
  SDL_Rect position;
  SDL_Color color;
};

struct Text : Element {
  std::string str;
};

struct Icon : Element {
  SDL_Texture* texture;
  SDL_Rect clip;
};

class HUD {
 public:
  ~HUD() = default;

  void Init(Window* window, ResourceManager* res_manager,
            SDL_Renderer* renderer);
  void Update(const int score, const int high_score, const int fps,
              const bool dead);
  void Draw(const bool dead);
  bool RetryClicked(SDL_Point* mouse_pos);

 private:
  void DrawText(const Text& t, const std::string font, const int size);
  void DrawIcon(const Icon& i);
  std::string ZeroPad(const int num);

  Text game_over_;
  Text current_score_;
  Text high_score_;
  Text fps_;
  Icon retry_;
  Window* window_;
  ResourceManager* res_manager_;
  SDL_Renderer* renderer_;
};

#endif  // ENTT_DINO_SRC_CORE_HUD_H_
