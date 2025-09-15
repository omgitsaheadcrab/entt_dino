/**
 * @file      spawn.h
 * @brief     Spawn system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2025-09-15
 * @copyright Copyright © 2025 Tobias Backer Dirks
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
  void CactiiOrPterodactyl();
  void Clouds();
  void Floors();
  void OnRestart();
  void MoonAndStars();

  static constexpr int kCloudMinSpacing_ = 300;
  static constexpr int kCloudMaxSpacing_ = 600;
  static constexpr int kMinStars_ = 1;
  static constexpr int kMaxStars_ = 3;
  static constexpr int kStarMinY_ = 20;
  static constexpr int kStarMaxY_ = 80;
  static constexpr int kStarMinX_ = 50;
  static constexpr int kStarMaxX_ = 750;
  static constexpr int kMaxEnemies_ = 2;
  static constexpr int kEnemyMinSpacing_ = 400;
  static constexpr int kEnemySpacingVariance_ = 200;
};

}  // namespace systems

#endif  // ENTT_DINO_SRC_SYS_SPAWN_H_
