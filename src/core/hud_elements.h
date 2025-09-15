/**
 * @file      hud_elements.h
 * @brief     HUD Elements
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2025-09-15
 * @copyright Copyright © 2025 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_CORE_HUD_ELEMENTS_H_
#define ENTT_DINO_SRC_CORE_HUD_ELEMENTS_H_

#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

#include <cstdint>
#include <string>

#include <entt/entity/registry.hpp>

#include "core/res_manager.h"

namespace omg {

namespace ui {

struct Element {
  SDL_Rect position;
  SDL_Color color;
};

struct Text : Element {
  std::string str;
  std::string font;
  uint32_t size;
};

struct Icon : Element {
  SDL_Texture* texture;
  SDL_Rect clip;

  bool Clicked(const SDL_Point& kMousePos) const;
};

Text CreateText(const std::string& kStr, const double kPosWScale,
                const double kPosHScale, const std::string& kFont,
                const uint32_t kSize, const SDL_Color& kColor,
                entt::registry* registry);
Icon CreateIcon(const std::string& kName, const double kPosWScale,
                const double kPosHScale, const SDL_Color& kColor,
                const omg::ResourceManager& res_manager,
                entt::registry* registry);

}  // namespace ui

}  // namespace omg

#endif  // ENTT_DINO_SRC_CORE_HUD_ELEMENTS_H_
