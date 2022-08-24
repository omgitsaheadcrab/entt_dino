/**
 * @file      game.h
 * @brief     Game logic and event loop
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-02
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_CORE_GAME_H_
#define ENTT_DINO_SRC_CORE_GAME_H_

#include <cstdint>

#include <entt/entity/registry.hpp>

#include "core/hud.h"
#include "core/res_manager.h"
#include "core/window.h"

namespace omg {

class Game {
 public:
  Game() = delete;
  Game(const int kWindowWidth, const int kWindowHeight);
  ~Game() = default;

  void Init();
  void HandleEvents();
  void Update(const double dt);
  void Render();
  void Run();

 private:
  entt::registry registry_;
  omg::HUD hud_;
  omg::ResourceManager res_manager_;
  omg::Window window_;
  static constexpr double kUpdatesPerSecond_ = 60.0;
};

}  // namespace omg

#endif  // ENTT_DINO_SRC_CORE_GAME_H_
