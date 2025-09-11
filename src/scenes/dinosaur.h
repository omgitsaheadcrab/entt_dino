/**
 * @file      dinosaur.h
 * @brief     Dinosaur scene
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-25
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_SCENES_DINOSAUR_H_
#define ENTT_DINO_SRC_SCENES_DINOSAUR_H_

#include <SDL2/SDL_pixels.h>

#include "core/base_scene.h"
#include "core/entity_manager.h"
#include "core/hud.h"

namespace scenes {

constexpr int kTransitionFrames = 40;  // Number of frames for color transition
constexpr int kTransitionPoints =
    50;  // Points interval for triggering transition

class Dinosaur : public omg::BaseScene {
 public:
  Dinosaur();
  virtual ~Dinosaur() = default;

  void Init() override;
  void HandleEvents() override;
  void Update(const double dt) override;
  void Render(const double alpha) override;

 private:
  omg::EntityManager entity_manager_;
  omg::HUD hud_;

  // Animated background transition state
  bool transitioning_;
  bool to_dark_;
  SDL_Color start_color_;
  SDL_Color end_color_;
  SDL_Color current_color_;
  int transition_frame_;
  int last_transition_score_;
  int last_score_for_transition_;
  bool just_restarted_;

  // Transition helpers
  void StartBackgroundTransition(bool to_dark, int score);
  void UpdateBackgroundTransition();
};

}  // namespace scenes

#endif  // ENTT_DINO_SRC_SCENES_DINOSAUR_H_
