/**
 * @file      render.cc
 * @brief     Render system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-13
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#include "sys/render.h"

#include <SDL2/SDL_render.h>

#include "comp/graphics/sprite.h"
#include "comp/graphics/transform.h"
#include "core/colors.h"
#include "core/game.h"
#include "core/window.h"
#include "ctx/game_states.h"
#include "ctx/graphics.h"

systems::Render::Render(omg::Window* window) : window_ {window} {}

void systems::Render::OnInit() {
  contexts::graphics::SetBounds(registry_, window_->window());
}

void systems::Render::Update(const double alpha) {
  auto color = colors::kDinoDark;
  if (contexts::game::GetDark(registry_)) {
    color = colors::kDinoLight;
  }

  const auto kView = registry_->view<components::graphics::Sprite,
                                     components::graphics::Transform>();
  kView.each([&](const auto& kSprite, const auto& kTransform) {
    SDL_SetTextureColorMod(kSprite.sheet, color.r, color.g, color.b);
    SDL_RenderCopy(window_->renderer(), kSprite.sheet, &kSprite.clip,
                   &kTransform.position);
  });
}
