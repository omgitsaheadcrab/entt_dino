/**
 * @file      game.h
 * @brief     Game logic and event loop
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2025-09-15
 * @copyright Copyright © 2025 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_CORE_GAME_H_
#define ENTT_DINO_SRC_CORE_GAME_H_

#include <cstdint>

#include "core/res_manager.h"
#include "core/scene_manager.h"
#include "core/window.h"

namespace omg {

class Game {
 public:
  Game() = delete;
  Game(const int kWindowWidth, const int kWindowHeight);
  ~Game() = default;

  uint32_t fps();
  omg::ResourceManager& res_manager();
  omg::SceneManager& scene_manager();
  omg::Window& window();

  void Run();
  void Quit();

 private:
  bool over_;
  uint32_t fps_;

  omg::ResourceManager res_manager_;
  omg::SceneManager scene_manager_;
  omg::Window window_;

  static constexpr double kUpdatesPerSecond_ = 60.0;
};

}  // namespace omg

#endif  // ENTT_DINO_SRC_CORE_GAME_H_
