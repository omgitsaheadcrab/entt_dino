/**
 * @file      closing_credits.h
 * @brief     Closing credits scene header
 * @author    Tobias Backer Dirks <omgitsaheadcrab@gmail.com>
 * @date      2024-06-10
 * @copyright Copyright © 2024 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_SCENES_CLOSING_CREDITS_H_
#define ENTT_DINO_SRC_SCENES_CLOSING_CREDITS_H_

#include <string>
#include <vector>

#include "core/base_scene.h"

namespace scenes {

class ClosingCredits : public omg::BaseScene {
 public:
  ClosingCredits();
  virtual ~ClosingCredits() = default;

  void Init() override;
  void HandleEvents() override;
  void Update(double dt) override;
  void Render(double alpha) override;

 private:
  std::vector<std::string> display_text_;
  std::string font_name_;
  int font_size_;
  SDL_Color font_color_;
};

}  // namespace scenes

#endif  // ENTT_DINO_SRC_SCENES_CLOSING_CREDITS_H_
