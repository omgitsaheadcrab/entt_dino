/**
 * @file      scene_manager.h
 * @brief     Scene manager
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-25
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_CORE_SCENE_MANAGER_H_
#define ENTT_DINO_SRC_CORE_SCENE_MANAGER_H_

#include <memory>
#include <string>
#include <vector>

#include "core/base_scene.h"
#include "core/fwd.h"

namespace omg {

class SceneManager {
 public:
  SceneManager() = delete;
  explicit SceneManager(omg::Game* game);
  ~SceneManager() = default;

  omg::BaseScene* current_scene() const;

  void AddScene(std::unique_ptr<omg::BaseScene> scene);
  void SetCurrentScene(const std::string& name);

 private:
  omg::Game* game_;

  std::vector<std::unique_ptr<omg::BaseScene>> scenes_;
  omg::BaseScene* current_scene_ = nullptr;
};

}  // namespace omg

#endif  // ENTT_DINO_SRC_CORE_SCENE_MANAGER_H_
