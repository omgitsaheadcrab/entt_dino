/**
 * @file      scene_manager.cc
 * @brief     Scene manager
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-25
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#include "core/scene_manager.h"

#include <memory>

#include "core/base_scene.h"
#include "core/game.h"

omg::SceneManager::SceneManager(omg::Game* game) : game_ {game} {}

omg::BaseScene* omg::SceneManager::current_scene() const {
  return current_scene_;
}

void omg::SceneManager::AddScene(std::unique_ptr<omg::BaseScene> scene) {
  scene->SetGame(game_);
  scene->Init();

  scenes_.push_back(std::move(scene));
}

bool omg::SceneManager::SetCurrentScene(const std::string& name) {
  for (auto& scene : scenes_) {
    if (scene->name() == name) {
      current_scene_ = scene.get();
      return true;
    }
  }
  return false;
}
