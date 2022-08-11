/**
 * @file      hud.cc
 * @brief     Game HUD
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-07-26
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#include "core/hud.h"

#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

#include <cstdint>
#include <string>

#include "core/hud_elements.h"
#include "core/res_manager.h"
#include "core/window.h"
#include "util/str.h"

constexpr SDL_Color dino_grey = {89, 86, 82};

void HUD::Manager::Init(Window* window, ResourceManager* res_manager) {
  window_ = window;
  res_manager_ = res_manager;
  renderer_ = window->renderer();
  fps_ = CreateText("00000", 0.02, 0.03, dino_grey);
  current_score_ = CreateText("00000", 0.92, 0.03, dino_grey);
  high_score_ = CreateText("", 0.78, 0.03, dino_grey);
  game_over_ = CreateText("G  A  M  E     O  V  E  R", 0.35, 0.40, dino_grey);
  retry_ = CreateIcon("retry", 0.48, 0.52, dino_grey);
}

void HUD::Manager::Update(const uint32_t score, const uint32_t high_score,
                          const uint32_t fps, const bool dead) {
  fps_.str = utils::ToStringZeroPad(fps, 5);
  current_score_.str = utils::ToStringZeroPad(score, 5);

  if (dead) {
    high_score_.str = "HI  " + utils::ToStringZeroPad(high_score, 5);
  }
}

void HUD::Manager::Draw(const bool dead) {
  DrawText(fps_, "8-bit-hud", 8);
  DrawText(current_score_, "8-bit-hud", 8);
  DrawText(high_score_, "8-bit-hud", 8);
  if (dead) {
    DrawText(game_over_, "8-bit-hud", 12);
    DrawIcon(retry_);
  }
}

bool HUD::Manager::RetryClicked(const SDL_Point& mouse_pos) const {
  return retry_.Clicked(mouse_pos);
}

void HUD::Manager::DrawText(const HUD::Text& t, const std::string& font,
                            const uint32_t size) {
  res_manager_->DrawText(t.str.c_str(), t.position.x, t.position.y, t.color,
                         font, size);
}

void HUD::Manager::DrawIcon(const HUD::Icon& i) {
  SDL_SetTextureColorMod(i.texture, dino_grey.r, dino_grey.g, dino_grey.b);
  SDL_RenderCopy(renderer_, i.texture, &i.clip, &i.position);
}

HUD::Text HUD::Manager::CreateText(const std::string& str,
                                   const double pos_w_scale,
                                   const double pos_h_scale,
                                   const SDL_Color& color) const {
  // TODO(omgitsaheadcrab): use WindowInfo entity for bounds
  return HUD::Text {SDL_Rect {static_cast<int>(800 * pos_w_scale),
                              static_cast<int>(244 * pos_h_scale), 0, 0},
                    color, str};
}

HUD::Icon HUD::Manager::CreateIcon(const std::string& name,
                                   const double pos_w_scale,
                                   const double pos_h_scale,
                                   const SDL_Color& color) const {
  // TODO(omgitsaheadcrab): use WindowInfo entity for bounds
  auto pos = SDL_Rect {static_cast<int>(800 * pos_w_scale),
                       static_cast<int>(244 * pos_h_scale), 0, 0};
  auto clips = res_manager_->GetSpriteClips(name);
  pos.h = clips[0].h;
  pos.w = clips[0].w;
  return HUD::Icon {pos, color,
                    res_manager_->sprite_textures.find(name)->second, clips[0]};
}
