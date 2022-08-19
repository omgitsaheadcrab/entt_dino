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

#include <entt/entity/registry.hpp>

#include "comp/entities/dino.h"
#include "comp/entity_states/dead.h"
#include "core/colors.h"
#include "core/hud_elements.h"
#include "core/res_manager.h"
#include "ctx/game_states.h"
#include "ctx/graphics.h"
#include "util/str.h"

void ui::HUD::Init(entt::registry* registry, SDL_Renderer* renderer,
                   ResourceManager* res_manager) {
  res_manager_ = res_manager;
  renderer_ = renderer;
  const auto font = "8-bit-hud";
  fps_ =
      ui::CreateText("00000", 0.02, 0.03, font, 8, colors::kDinoGrey, registry);
  current_score_ =
      ui::CreateText("00000", 0.92, 0.03, font, 8, colors::kDinoGrey, registry);
  high_score_ =
      ui::CreateText("", 0.78, 0.03, font, 8, colors::kDinoGrey, registry);
  game_over_ = ui::CreateText("G  A  M  E     O  V  E  R", 0.35, 0.40, font, 12,
                              colors::kDinoGrey, registry);
  retry_ = ui::CreateIcon("retry", 0.48, 0.52, colors::kDinoGrey, res_manager_,
                          registry);
}

void ui::HUD::Update(entt::registry* registry) {
  const auto kScore = contexts::game_states::GetScore(registry).value;
  const auto kHighScore = contexts::game_states::GetHighscore(registry).value;
  const auto kFps = contexts::graphics::GetFPS(registry).value;

  fps_.str = utils::ToStringZeroPad(kFps, 5);
  current_score_.str = utils::ToStringZeroPad(kScore, 5);

  const auto kDinoDead =
      registry
          ->view<components::entities::Dino, components::entity_states::Dead>();
  if (kDinoDead.size_hint()) {
    high_score_.str = "HI  " + utils::ToStringZeroPad(kHighScore, 5);
  }
}

void ui::HUD::Draw(entt::registry* registry) {
  DrawText(fps_);
  DrawText(current_score_);
  DrawText(high_score_);

  const auto kDinoDead =
      registry
          ->view<components::entities::Dino, components::entity_states::Dead>();
  if (kDinoDead.size_hint()) {
    DrawText(game_over_);
    DrawIcon(retry_);
  }
}

bool ui::HUD::RetryClicked(const SDL_Point& kMousePos) const {
  return retry_.Clicked(kMousePos);
}

void ui::HUD::DrawText(const ui::Text& kText) const {
  res_manager_->DrawText(kText.str.c_str(), kText.position, kText.color,
                         kText.font, kText.size);
}

void ui::HUD::DrawIcon(const ui::Icon& kIcon) const {
  SDL_SetTextureColorMod(kIcon.texture, colors::kDinoGrey.r,
                         colors::kDinoGrey.g, colors::kDinoGrey.b);
  SDL_RenderCopy(renderer_, kIcon.texture, &kIcon.clip, &kIcon.position);
}
