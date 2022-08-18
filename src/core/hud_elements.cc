/**
 * @file      hud_elements.cc
 * @brief     HUD Elements
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-02
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#include "core/hud_elements.h"

#include <SDL2/SDL_rect.h>

#include <entt/entity/registry.hpp>

#include "core/res_manager.h"
#include "ctx/graphics.h"

bool ui::Icon::Clicked(const SDL_Point& kMousePos) const {
  return (SDL_PointInRect(&kMousePos, &(this)->position));
}

ui::Text ui::CreateText(const std::string& kStr, const double kPosWScale,
                        const double kPosHScale, const std::string& kFont,
                        const uint32_t kSize, const SDL_Color& kColor,
                        entt::registry* registry) {
  const auto& kBounds = contexts::graphics::GetBounds(registry);
  const auto pos =
      SDL_Rect {static_cast<int>(kBounds.position.w * kPosWScale),
                static_cast<int>(kBounds.position.h * kPosHScale), 0, 0};
  return ui::Text {pos, kColor, kStr, kFont, kSize};
}

ui::Icon ui::CreateIcon(const std::string& kName, const double kPosWScale,
                        const double kPosHScale, const SDL_Color& kColor,
                        ResourceManager* res_manager,
                        entt::registry* registry) {
  const auto& kBounds = contexts::graphics::GetBounds(registry);
  const auto kClips = res_manager->GetSpriteClips(kName);
  auto pos = SDL_Rect {static_cast<int>(kBounds.position.w * kPosWScale),
                       static_cast<int>(kBounds.position.h * kPosHScale), 0, 0};
  pos.h = kClips[0].h;
  pos.w = kClips[0].w;
  return ui::Icon {pos, kColor, res_manager->GetSpriteTexture(kName),
                   kClips[0]};
}
