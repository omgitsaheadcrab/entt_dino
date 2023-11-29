/**
 * @file      dinosaur.h
 * @brief     Dinosaur scene
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-25
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_SCENES_DINOSAUR_H_
#define ENTT_DINO_SRC_SCENES_DINOSAUR_H_

#include "core/base_scene.h"
#include "core/entity_manager.h"

namespace scenes {

class Dinosaur : public omg::BaseScene {
 public:
  Dinosaur();
  virtual ~Dinosaur() = default;

  void Init() override;
  void HandleEvents() override;
  void Update(const double dt) override;
  void Render(const double alpha) override;

 private:
  void OnRestart();
  omg::EntityManager entity_manager_;
};

}  // namespace scenes

#endif  // ENTT_DINO_SRC_SCENES_DINOSAUR_H_
