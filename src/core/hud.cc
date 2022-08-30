/**
 * @file      hud.cc
 * @brief     Game HUD
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-07-26
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#include "core/hud.h"

#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>

#include <cstdint>

#include <entt/entity/registry.hpp>

#include "comp/entities/dino.h"
#include "comp/entity_states/dead.h"
#include "core/colors.h"
#include "core/game.h"
#include "core/hud_elements.h"
#include "core/res_manager.h"
#include "ctx/game_states.h"
#include "util/str.h"

void omg::HUD::Init(entt::registry* registry, omg::Game* game) {
  game_ = game;
  registry_ = registry;

  const auto font = "8-bit-hud";
  fps_ = omg::ui::CreateText("00000", 0.02, 0.03, font, 8, colors::kDinoDark,
                             registry);
  current_score_ = omg::ui::CreateText("00000", 0.92, 0.03, font, 8,
                                       colors::kDinoDark, registry);
  high_score_ = omg::ui::CreateText("", 0.78, 0.03, font, 8,
                                    colors::kHighscoreDark, registry);
  game_over_ = omg::ui::CreateText("G  A  M  E     O  V  E  R", 0.35, 0.40,
                                   font, 12, colors::kDinoDark, registry);
  retry_ = omg::ui::CreateIcon("retry", 0.48, 0.52, colors::kDinoDark,
                               game_->res_manager(), registry);
}

void omg::HUD::Update() {
  const auto kDark = contexts::game_states::GetDark(registry_);
  const auto kScore = contexts::game_states::GetScore(registry_).value;
  const auto kHighScore = contexts::game_states::GetHighscore(registry_).value;

  fps_.str = utils::ToStringZeroPad(game_->fps(), 5);
  current_score_.str = utils::ToStringZeroPad(kScore, 5);

  auto color = colors::kDinoDark;
  auto color_hi = colors::kHighscoreDark;
  if (kDark) {
    color = colors::kDinoLight;
    color_hi = colors::kHighscoreLight;
  }
  fps_.color = color;
  current_score_.color = color;
  high_score_.color = color_hi;
  game_over_.color = color;
  retry_.color = color;

  const auto kDinoDead =
      registry_
          ->view<components::entities::Dino, components::entity_states::Dead>();
  if (kDinoDead.size_hint()) {
    high_score_.str = "HI  " + utils::ToStringZeroPad(kHighScore, 5);
  }
}

void omg::HUD::Draw() {
  DrawText(fps_);
  DrawText(current_score_);
  DrawText(high_score_);

  const auto kDinoDead =
      registry_
          ->view<components::entities::Dino, components::entity_states::Dead>();
  if (kDinoDead.size_hint()) {
    DrawText(game_over_);
    DrawIcon(retry_);
  }
}

bool omg::HUD::RetryClicked(const SDL_Point& kMousePos) const {
  return retry_.Clicked(kMousePos);
}

void omg::HUD::DrawText(const omg::ui::Text& kText) const {
  game_->res_manager().DrawText(kText.str.c_str(), kText.position, kText.color,
                                kText.font, kText.size);
}

void omg::HUD::DrawIcon(const omg::ui::Icon& kIcon) const {
  SDL_SetTextureColorMod(kIcon.texture, kIcon.color.r, kIcon.color.g,
                         kIcon.color.b);
  SDL_RenderCopy(game_->window().renderer(), kIcon.texture, &kIcon.clip,
                 &kIcon.position);
}
