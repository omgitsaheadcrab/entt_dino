/**
 * @file      base_scene.h
 * @brief     Base scene
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-24
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_CORE_BASE_SCENE_H_
#define ENTT_DINO_SRC_CORE_BASE_SCENE_H_

#include "core/game.h"
#include "core/hud.h"
#include "core/res_manager.h"
#include "core/window.h"
// #include "core/scene_manager.h"

namespace omg {

class BaseScene {
 public:
  BaseScene();
  virtual ~BaseScene();

 protected:
  omg::Game* game_;
  // SceneManager* scene_manager_;
  omg::HUD* hud_;
  omg::ResourceManager* res_manager_;
  omg::Window* window_;
};

}  // namespace omg

#endif  // ENTT_DINO_SRC_CORE_BASE_SCENE_H_
