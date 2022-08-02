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
#include <SDL2/SDL_render.h>

#include <string>

#include "core/hud_elements.h"
#include "core/res_manager.h"
#include "core/window.h"

class HUD {
 public:
  ~HUD() = default;

  void Init(Window* window, ResourceManager* res_manager);
  void Update(const int score, const int high_score, const int fps,
              const bool dead);
  void Draw(const bool dead);
  bool RetryClicked(SDL_Point* mouse_pos);

 private:
  void DrawText(const HUDElements::Text& t, const std::string font,
                const int size);
  void DrawIcon(const HUDElements::Icon& i);
  std::string ZeroPad(const int num);

  HUDElements::Text game_over_;
  HUDElements::Text current_score_;
  HUDElements::Text high_score_;
  HUDElements::Text fps_;
  HUDElements::Icon retry_;
  Window* window_;
  ResourceManager* res_manager_;
  SDL_Renderer* renderer_;
};

#endif  // ENTT_DINO_SRC_CORE_HUD_H_
