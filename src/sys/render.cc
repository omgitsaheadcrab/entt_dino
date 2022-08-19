/**
 * @file      render.cc
 * @brief     Render system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-13
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#include "sys/render.h"

#include <SDL2/SDL_render.h>
#include <SDL_rect.h>

#include <entt/entity/registry.hpp>

#include "comp/graphics/sprite.h"
#include "comp/graphics/transform.h"
#include "core/colors.h"
#include "ctx/game_states.h"

void systems::render::Sprites(SDL_Renderer* renderer,
                              entt::registry* registry) {
  auto color = colors::kDinoDark;
  if (contexts::game_states::GetDark(registry)) {
    color = colors::kDinoLight;
  }

  const auto kView = registry->view<components::graphics::Sprite,
                                    components::graphics::Transform>();
  kView.each([&](const auto& kSprite, const auto& kTransform) {
    SDL_SetTextureColorMod(kSprite.sheet, color.r, color.g, color.b);
    SDL_RenderCopy(renderer, kSprite.sheet, &kSprite.clip,
                   &kTransform.position);
  });
}
