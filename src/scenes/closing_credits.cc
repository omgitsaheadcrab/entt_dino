/**
 * @file      closing_credits.cc
 * @brief     Closing credits scene
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2025-09-15
 * @copyright Copyright © 2025 Tobias Backer Dirks
 */

#include "scenes/closing_credits.h"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>

#include <string>

#include "core/colors.h"
#include "core/game.h"
#include "core/res_manager.h"
#include "core/window.h"

namespace scenes {

ClosingCredits::ClosingCredits()
    : omg::BaseScene("closing_credits"),
      display_text_({"Tobias Backer Dirks <omgitsaheadcrab@gmail.com>", "",
                     "github.com/omgitsaheadcrab/entt_dino", "MIT 2025", "",
                     "Press any key to exit"}),
      font_name_("8-bit-hud"),
      font_size_(12),
      font_color_(colors::kDinoDark) {}

void ClosingCredits::Init() {
  // No resource loading needed for closing credits
}

void ClosingCredits::HandleEvents() {
  SDL_Event& event = game_->window().event();
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_KEYDOWN || event.type == SDL_MOUSEBUTTONDOWN ||
        event.type == SDL_QUIT) {
      game_->Quit();
    }
  }
}

void ClosingCredits::Update(double dt) {
  // No update logic needed for static credits
}

void ClosingCredits::Render(double alpha) {
  SDL_Renderer* renderer = game_->window().renderer();
  SDL_Color bg_color = colors::kBackgroundLight;
  SDL_SetRenderDrawColor(renderer, bg_color.r, bg_color.g, bg_color.b,
                         bg_color.a);
  SDL_RenderClear(renderer);

  int char_width = 12;
  int char_height = 18;
  int y = 30;
  for (const auto& line : display_text_) {
    SDL_Rect text_rect;
    text_rect.w = line.size() * char_width;
    text_rect.h = char_height;
    text_rect.x = (800 - text_rect.w) / 2;
    text_rect.y = y;
    game_->res_manager().DrawText(line, text_rect, font_color_, font_name_,
                                  font_size_);
    y += char_height + 16;
  }

  SDL_RenderPresent(renderer);
}

}  // namespace scenes
