/**
 * @file      hud.h
 * @brief     Game HUD
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-07-26
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_CORE_HUD_H_
#define ENTT_DINO_SRC_CORE_HUD_H_

#include <SDL2/SDL_pixels.h>

#include <entt/entity/registry.hpp>

#include "core/fwd.h"
#include "core/hud_elements.h"
#include "entt/entity/fwd.hpp"

namespace omg {

class HUD {
 public:
  HUD() = default;
  ~HUD() = default;

  void Init(entt::registry* registry, omg::Game* game);
  void Update();
  void Draw();
  bool RetryClicked(const SDL_Point& kMousePos) const;

 private:
  void DrawText(const omg::ui::Text& kText) const;
  void DrawIcon(const omg::ui::Icon& kIcon) const;

  omg::ui::Icon retry_;
  omg::ui::Text fps_;
  omg::ui::Text game_over_;
  omg::ui::Text current_score_;
  omg::ui::Text high_score_;

  omg::Game* game_;
  entt::registry* registry_;
};

}  // namespace omg

#endif  // ENTT_DINO_SRC_CORE_HUD_H_
