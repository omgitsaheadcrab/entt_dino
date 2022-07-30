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

#include "core/res_manager.h"
#include "core/window.h"

struct Element {
  std::string text;
  SDL_Color color;
  SDL_Rect position;
  int value = 0;
};

class HUD {
 public:
  ~HUD() = default;

  void Init(Window* window, ResourceManager* res_manager);
  void Update(const int score, const int fps, const bool dead);
  void Draw(const bool dead);

 private:
  void DrawElement(const Element& e, const std::string font, const int size);
  std::string ZeroPad(const int num);

  Element game_over_;
  Element current_score_;
  Element high_score_;
  Element fps_;
  Window* window_;
  ResourceManager* res_manager_;
};

#endif  // ENTT_DINO_SRC_CORE_HUD_H_
