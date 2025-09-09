/**
 * @file      opening_credits.h
 * @brief     Opening credits scene
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2024-06-10
 * @copyright Copyright © 2024 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_SCENES_OPENING_CREDITS_H_
#define ENTT_DINO_SRC_SCENES_OPENING_CREDITS_H_

#include "core/base_scene.h"
#include "core/entity_manager.h"

namespace scenes {

class OpeningCredits : public omg::BaseScene {
 public:
  OpeningCredits();
  virtual ~OpeningCredits() = default;

  void Init() override;
  void HandleEvents() override;
  void Update(const double dt) override;
  void Render(const double alpha) override;

 private:
  omg::EntityManager entity_manager_;
  std::string display_text_;
  std::string font_name_;
  int font_size_;
  SDL_Color font_color_;
};

}  // namespace scenes

#endif  // ENTT_DINO_SRC_SCENES_OPENING_CREDITS_H_
