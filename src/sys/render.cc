/**
 * @file      render.cc
 * @brief     Render system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-13
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#include "sys/render.h"

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>

#include "comp/graphics/sprite.h"
#include "comp/graphics/transform.h"
#include "comp/graphics/animation.h"
#include "core/colors.h"
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

  // Animate pterodactyls (and any entity with Animation component)
  auto animView = registry_->view<components::graphics::Sprite, components::graphics::Animation>();
  uint32_t dt = static_cast<uint32_t>(alpha);
  animView.each([dt](auto& sprite, auto& anim) {
    anim.elapsed += dt;
    if (anim.elapsed >= anim.frame_duration) {
      anim.elapsed = 0;
      anim.current_frame = (anim.current_frame + 1) % anim.frames.size();
      sprite.clip = anim.frames[anim.current_frame];
    }
  });

  const auto kView = registry_->view<components::graphics::Sprite,
                                     components::graphics::Transform>();
  kView.each([&](const auto& kSprite, const auto& kTransform) {
    SDL_SetTextureColorMod(kSprite.sheet, color.r, color.g, color.b);
    SDL_RenderCopy(window_->renderer(), kSprite.sheet, &kSprite.clip,
                   &kTransform.position);
  });
}
