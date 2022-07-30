/**
 * @file      hud.cc
 * @brief     Game HUD
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-07-26
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#include "core/hud.h"

#include <string>

#include "SDL_rect.h"
#include "core/res_manager.h"
#include "core/window.h"

const SDL_Color dino_grey = {89, 86, 82};

void HUD::Init(Window* window, ResourceManager* res_manager) {
  window_ = window;
  res_manager_ = res_manager;
  fps_ = Element {"00000", dino_grey,
                  SDL_Rect {static_cast<int>(window->bounds().w * 0.02),
                            static_cast<int>(window->bounds().h * 0.03), 0, 0}};
  current_score_ =
      Element {"00000", dino_grey,
               SDL_Rect {static_cast<int>(window->bounds().w * 0.92),
                         static_cast<int>(window->bounds().h * 0.03), 0, 0}};
  high_score_ =
      Element {"", dino_grey,
               SDL_Rect {static_cast<int>(window->bounds().w * 0.78),
                         static_cast<int>(window->bounds().h * 0.03), 0, 0}};
  game_over_ =
      Element {"G  A  M  E     O  V  E  R", dino_grey,
               SDL_Rect {static_cast<int>(window->bounds().w * 0.35),
                         static_cast<int>(window->bounds().h * 0.40), 0, 0}};
}

void HUD::Update(const int score, const int high_score, const int fps,
                 const bool dead) {
  fps_.text = ZeroPad(fps);
  current_score_.text = ZeroPad(score);

  if (dead) {
    high_score_.text = "HI  " + ZeroPad(high_score);
  }
}

void HUD::Draw(const bool dead) {
  DrawElement(fps_, "8-bit-hud", 8);
  DrawElement(current_score_, "8-bit-hud", 8);
  DrawElement(high_score_, "8-bit-hud", 8);
  if (dead) {
    DrawElement(game_over_, "8-bit-hud", 12);
  }
}

void HUD::DrawElement(const Element& e, const std::string font,
                      const int size) {
  res_manager_->DrawText(e.text.c_str(), e.position.x, e.position.y, e.color,
                         font, size);
}

std::string HUD::ZeroPad(const int num) {
  auto s = std::to_string(num);
  unsigned int number_of_zeros = 5 - s.length();
  s.insert(0, number_of_zeros, '0');
  return s;
}
