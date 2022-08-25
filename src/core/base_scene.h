/**
 * @file      base_scene.h
 * @brief     Base scene
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-24
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_CORE_BASE_SCENE_H_
#define ENTT_DINO_SRC_CORE_BASE_SCENE_H_

#include <string>

#include "core/game.h"
#include "core/hud.h"
#include "core/res_manager.h"
#include "core/window.h"
// #include "core/scene_manager.h"

#include <SDL2/SDL_events.h>

namespace omg {

class BaseScene {
 public:
  BaseScene() = delete;
  explicit BaseScene(const std::string& name);
  virtual ~BaseScene();

  const std::string& name() const;

  void HandleBaseEvents(const SDL_Event& event);
  void SetGame(omg::Game* game);

  virtual void Init() = 0;
  virtual void HandleEvents() = 0;
  virtual void Update(const double dt) = 0;
  virtual void Render() = 0;

 protected:
  omg::Game* game_;
  // SceneManager* scene_manager_;
  omg::HUD* hud_;
  omg::ResourceManager* res_manager_;
  omg::Window* window_;

 private:
  std::string name_;
};

}  // namespace omg

#endif  // ENTT_DINO_SRC_CORE_BASE_SCENE_H_
