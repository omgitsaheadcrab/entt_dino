/**
 * @file      hud.h
 * @brief     Game HUD
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-07-26
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_CORE_HUD_H_
#define ENTT_DINO_SRC_CORE_HUD_H_

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>

#include <cstdint>
#include <string>

#include <entt/entity/registry.hpp>

#include "core/hud_elements.h"
#include "core/res_manager.h"

namespace ui {

class HUD {
 public:
  ~HUD() = default;

  void Init(entt::registry* registry, SDL_Renderer* renderer,
            ResourceManager* res_manager);
  void Update(entt::registry* registry);
  void Draw(entt::registry* registry);
  bool RetryClicked(const SDL_Point& kMousePos) const;

 private:
  void DrawText(const ui::Text& kText) const;
  void DrawIcon(const ui::Icon& kIcon) const;

  ui::Icon retry_;
  ui::Text fps_;
  ui::Text game_over_;
  ui::Text current_score_;
  ui::Text high_score_;
  SDL_Renderer* renderer_;
  ResourceManager* res_manager_;
};

}  // namespace ui

#endif  // ENTT_DINO_SRC_CORE_HUD_H_
