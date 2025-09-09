/**
 * @file      opening_credits.cc
 * @brief     Opening credits scene
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2024-06-10
 * @copyright Copyright © 2024 Tobias Backer Dirks
 */

#include "scenes/opening_credits.h"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>

#include <string>

#include "core/colors.h"
#include "core/game.h"
#include "core/res_manager.h"
#include "core/window.h"

namespace scenes {

OpeningCredits::OpeningCredits()
    : omg::BaseScene("opening_credits"),
      display_text_("Press any key to start"),
      font_name_("8-bit-hud"),
      font_size_(12),
      font_color_(colors::kDinoDark),
      logo_texture_(nullptr) {}

void OpeningCredits::Init() {
  // Load logo sprite
  logo_texture_ = game_->res_manager().GetSpriteTexture("logo");
  const auto& kClips = game_->res_manager().GetSpriteClips("logo", "logo");

  logo_rect_.w = kClips.front().w;
  logo_rect_.h = kClips.front().h;
  logo_rect_.x = (800 - logo_rect_.w) / 2;
  logo_rect_.y = 40;  // Place near the top
}

void OpeningCredits::HandleEvents() {
  SDL_Event& event = game_->window().event();
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_KEYDOWN || event.type == SDL_MOUSEBUTTONDOWN) {
      game_->scene_manager().SetCurrentScene("dinosaur");
    }
    if (event.type == SDL_QUIT) {
      game_->scene_manager().SetCurrentScene("closing_credits");
    }
  }
}

void OpeningCredits::Update(double dt) {
  // No update logic needed for static credits
}

void OpeningCredits::Render(double alpha) {
  SDL_Renderer* renderer = game_->window().renderer();
  // Use light background for opening credits
  SDL_Color bg_color = colors::kBackgroundLight;
  SDL_SetRenderDrawColor(renderer, bg_color.r, bg_color.g, bg_color.b,
                         bg_color.a);
  SDL_RenderClear(renderer);

  // Draw logo if loaded
  if (logo_texture_) {
    SDL_Color fg_color = colors::kDinoDark;
    SDL_SetTextureColorMod(logo_texture_, fg_color.r, fg_color.g, fg_color.b);
    SDL_RenderCopy(renderer, logo_texture_, nullptr, &logo_rect_);
  }

  // Center the text
  SDL_Rect text_rect;
  int char_width = 12;
  int char_height = 18;
  text_rect.w = display_text_.size() * char_width;
  text_rect.h = char_height;
  text_rect.x = (800 - text_rect.w) / 2;
  text_rect.y = logo_rect_.y + logo_rect_.h + 48;

  game_->res_manager().DrawText(display_text_, text_rect, font_color_,
                                font_name_, font_size_);

  SDL_RenderPresent(renderer);
}

}  // namespace scenes
