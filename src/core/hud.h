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
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>

#include <string>

#include "core/hud_elements.h"
#include "core/res_manager.h"
#include "core/window.h"

namespace HUD {

class Manager {
 public:
  ~Manager() = default;

  void Init(Window* window, ResourceManager* res_manager);
  void Update(const int score, const int high_score, const int fps,
              const bool dead);
  void Draw(const bool dead);
  bool RetryClicked(const SDL_Point& mouse_pos) const;

 private:
  void DrawText(const HUD::Text& t, const std::string& font, const int size);
  void DrawIcon(const HUD::Icon& i);
  HUD::Text CreateText(const std::string& str, const double pos_w_scale,
                       const double pos_h_scale, const SDL_Color& color) const;
  HUD::Icon CreateIcon(const std::string& name, const double pos_w_scale,
                       const double pos_h_scale, const SDL_Color& color) const;
  std::string ZeroPad(const int num) const;

  HUD::Icon retry_;
  HUD::Text fps_;
  HUD::Text game_over_;
  HUD::Text current_score_;
  HUD::Text high_score_;
  Window* window_;
  ResourceManager* res_manager_;
  SDL_Renderer* renderer_;
};

}  // namespace HUD

#endif  // ENTT_DINO_SRC_CORE_HUD_H_
