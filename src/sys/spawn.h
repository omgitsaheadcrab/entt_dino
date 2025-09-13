/**
 * @file      spawn.h
 * @brief     Spawn system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-11-18
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_SYS_SPAWN_H_
#define ENTT_DINO_SRC_SYS_SPAWN_H_

#include "core/base_system.h"

namespace systems {

class Spawn : public omg::BaseSystem {
 public:
  Spawn() = default;
  virtual ~Spawn() = default;

  void Update(const double dt) override;

 protected:
  void OnInit() override;

 private:
  void CactiiOrPterodactyl();  // Renamed from Cactii
  void Clouds();
  void Floors();
  void OnRestart();
  void MoonAndStars();

  // Cloud and star spawn constants as private members (with trailing _)
  static constexpr int kCloudMinSpacing_ = 300;
  static constexpr int kCloudMaxSpacing_ = 600;

  static constexpr int kMinStars_ = 1;
  static constexpr int kMaxStars_ = 3;
  static constexpr int kStarMinY_ = 20;
  static constexpr int kStarMaxY_ = 80;
  static constexpr int kStarMinX_ = 50;
  static constexpr int kStarMaxX_ = 750;
};

}  // namespace systems

#endif  // ENTT_DINO_SRC_SYS_SPAWN_H_
