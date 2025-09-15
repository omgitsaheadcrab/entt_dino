/**
 * @file      opening_credits.h
 * @brief     Opening credits scene
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2025-09-15
 * @copyright Copyright © 2025 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_SCENES_OPENING_CREDITS_H_
#define ENTT_DINO_SRC_SCENES_OPENING_CREDITS_H_

#include <SDL2/SDL.h>

#include <string>

#include "core/base_scene.h"

namespace scenes {

class OpeningCredits : public omg::BaseScene {
 public:
  OpeningCredits();
  virtual ~OpeningCredits() = default;

  void Init() override;
  void HandleEvents() override;
  void Update(double dt) override;
  void Render(double alpha) override;

 private:
  std::string display_text_;
  std::string font_name_;
  int font_size_;
  SDL_Color font_color_;
  SDL_Texture* logo_texture_;
  SDL_Rect logo_rect_;
};

}  // namespace scenes

#endif  // ENTT_DINO_SRC_SCENES_OPENING_CREDITS_H_
