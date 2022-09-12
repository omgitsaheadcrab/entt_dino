/**
 * @file      base_scene.h
 * @brief     Base scene
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-24
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_CORE_BASE_SCENE_H_
#define ENTT_DINO_SRC_CORE_BASE_SCENE_H_

#include <SDL2/SDL_events.h>

#include <string>

#include "core/fwd.h"

namespace omg {

class BaseScene {
 public:
  BaseScene() = delete;
  explicit BaseScene(const std::string& scene_name);
  ~BaseScene() = default;

  std::string& name();

  void HandleBaseEvents(const SDL_Event* event);
  void SetGame(omg::Game* game);

  virtual void Init() = 0;
  virtual void HandleEvents() = 0;
  virtual void Update(const double dt) = 0;
  virtual void Render(const double alpha) = 0;

 protected:
  omg::Game* game_;

  omg::HUD* hud_;
  omg::ResourceManager* res_manager_;
  omg::SceneManager* scene_manager_;
  omg::Window* window_;

 private:
  std::string name_;
};

}  // namespace omg

#endif  // ENTT_DINO_SRC_CORE_BASE_SCENE_H_
