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
#include "SDL_render.h"
#include "core/res_manager.h"
#include "core/window.h"

const SDL_Color dino_grey = {89, 86, 82};

void HUD::Init(Window* window, ResourceManager* res_manager,
               SDL_Renderer* renderer) {
  window_ = window;
  res_manager_ = res_manager;
  renderer_ = renderer;
  fps_ = HUDElements::Text {
      SDL_Rect {static_cast<int>(window->bounds().w * 0.02),
                static_cast<int>(window->bounds().h * 0.03), 0, 0},
      dino_grey, "00000"};
  current_score_ = HUDElements::Text {
      SDL_Rect {static_cast<int>(window->bounds().w * 0.92),
                static_cast<int>(window->bounds().h * 0.03), 0, 0},
      dino_grey, "00000"};
  high_score_ = HUDElements::Text {
      SDL_Rect {static_cast<int>(window->bounds().w * 0.78),
                static_cast<int>(window->bounds().h * 0.03), 0, 0},
      dino_grey, ""};
  game_over_ = HUDElements::Text {
      SDL_Rect {static_cast<int>(window->bounds().w * 0.35),
                static_cast<int>(window->bounds().h * 0.40), 0, 0},
      dino_grey, "G  A  M  E     O  V  E  R"};
  // Move to create Retry
  auto pos = SDL_Rect {static_cast<int>(window->bounds().w * 0.48),
                       static_cast<int>(window->bounds().h * 0.52), 0, 0};
  auto clips = res_manager_->GetSpriteClips("retry");
  pos.h = clips[0].h;
  pos.w = clips[0].w;
  retry_ = HUDElements::Icon {
      pos, dino_grey, res_manager->sprite_textures.find("retry")->second,
      clips[0]};
}

void HUD::Update(const int score, const int high_score, const int fps,
                 const bool dead) {
  fps_.str = ZeroPad(fps);
  current_score_.str = ZeroPad(score);

  if (dead) {
    high_score_.str = "HI  " + ZeroPad(high_score);
  }
}

void HUD::Draw(const bool dead) {
  DrawText(fps_, "8-bit-hud", 8);
  DrawText(current_score_, "8-bit-hud", 8);
  DrawText(high_score_, "8-bit-hud", 8);
  if (dead) {
    DrawText(game_over_, "8-bit-hud", 12);
    DrawIcon(retry_);
  }
}

bool HUD::RetryClicked(SDL_Point* mouse_pos) {
  return (SDL_PointInRect(mouse_pos, &retry_.position));
}

void HUD::DrawText(const HUDElements::Text& t, const std::string font,
                   const int size) {
  res_manager_->DrawText(t.str.c_str(), t.position.x, t.position.y, t.color,
                         font, size);
}

void HUD::DrawIcon(const HUDElements::Icon& i) {
  SDL_SetTextureColorMod(i.texture, dino_grey.r, dino_grey.g, dino_grey.b);
  SDL_RenderCopy(renderer_, i.texture, &i.clip, &i.position);
}

std::string HUD::ZeroPad(const int num) {
  auto s = std::to_string(num);
  unsigned int number_of_zeros = 5 - s.length();
  s.insert(0, number_of_zeros, '0');
  return s;
}
