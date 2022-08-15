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

#include "core/colors.h"
#include "core/hud_elements.h"
#include "core/res_manager.h"
#include "core/window.h"
#include "ctx/game_states.h"
#include "ctx/graphics.h"
#include "util/str.h"

void HUD::Manager::Init(Window* window, ResourceManager* res_manager) {
  window_ = window;
  res_manager_ = res_manager;
  renderer_ = window->renderer();
  fps_ = CreateText("00000", 0.02, 0.03, colors::kDinoGrey);
  current_score_ = CreateText("00000", 0.92, 0.03, colors::kDinoGrey);
  high_score_ = CreateText("", 0.78, 0.03, colors::kDinoGrey);
  game_over_ =
      CreateText("G  A  M  E     O  V  E  R", 0.35, 0.40, colors::kDinoGrey);
  retry_ = CreateIcon("retry", 0.48, 0.52, colors::kDinoGrey);
}

void HUD::Manager::Update(entt::registry* registry, const bool kDead) {
  const auto kScore = contexts::game_states::GetScore(registry).value;
  const auto kHighScore = contexts::game_states::GetHighscore(registry).value;
  const auto kFps = contexts::graphics::GetFPS(registry).value;

  fps_.str = utils::ToStringZeroPad(kFps, 5);
  current_score_.str = utils::ToStringZeroPad(kScore, 5);

  if (kDead) {
    high_score_.str = "HI  " + utils::ToStringZeroPad(kHighScore, 5);
  }
}

void HUD::Manager::Draw(const bool kDead) {
  DrawText(fps_, "8-bit-hud", 8);
  DrawText(current_score_, "8-bit-hud", 8);
  DrawText(high_score_, "8-bit-hud", 8);
  if (kDead) {
    DrawText(game_over_, "8-bit-hud", 12);
    DrawIcon(retry_);
  }
}

bool HUD::Manager::RetryClicked(const SDL_Point& kMousePos) const {
  return retry_.Clicked(kMousePos);
}

void HUD::Manager::DrawText(const HUD::Text& kText, const std::string& kFont,
                            const uint32_t kSize) {
  res_manager_->DrawText(kText.str.c_str(), kText.position.x, kText.position.y,
                         kText.color, kFont, kSize);
}

void HUD::Manager::DrawIcon(const HUD::Icon& kIcon) {
  SDL_SetTextureColorMod(kIcon.texture, colors::kDinoGrey.r,
                         colors::kDinoGrey.g, colors::kDinoGrey.b);
  SDL_RenderCopy(renderer_, kIcon.texture, &kIcon.clip, &kIcon.position);
}

HUD::Text HUD::Manager::CreateText(const std::string& kStr,
                                   const double kPosWScale,
                                   const double kPosHScale,
                                   const SDL_Color& kColor) const {
  // TODO(omgitsaheadcrab): use WindowInfo entity for bounds
  return HUD::Text {SDL_Rect {static_cast<int>(800 * kPosWScale),
                              static_cast<int>(244 * kPosHScale), 0, 0},
                    kColor, kStr};
}

HUD::Icon HUD::Manager::CreateIcon(const std::string& kName,
                                   const double kPosWScale,
                                   const double kPosHScale,
                                   const SDL_Color& kColor) const {
  // TODO(omgitsaheadcrab): use WindowInfo entity for bounds
  const auto kClips = res_manager_->GetSpriteClips(kName);
  auto pos = SDL_Rect {static_cast<int>(800 * kPosWScale),
                       static_cast<int>(244 * kPosHScale), 0, 0};
  pos.h = kClips[0].h;
  pos.w = kClips[0].w;
  return HUD::Icon {pos, kColor, res_manager_->GetSpriteTexture(kName),
                    kClips[0]};
}
