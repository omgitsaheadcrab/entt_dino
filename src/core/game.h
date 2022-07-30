/**
 * @file      game.h
 * @brief     Game logic and event loop.
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-02
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_CORE_GAME_H_
#define ENTT_DINO_SRC_CORE_GAME_H_

#include <cstdint>
#include <set>

#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>

#include "core/hud.h"
#include "core/res_manager.h"
#include "core/window.h"

class Game {
 public:
  Game() = delete;
  Game(const int kWindowWidth, const int kWindowHeight);
  ~Game() = default;

  void Init();
  void HandleEvents();
  void Update();
  void Render();
  void Run();

 private:
  uint32_t base_speed_;
  std::set<entt::entity> cloud_entities_;
  std::set<entt::entity> floor_entities_;
  const double kUpdatesPerSecond_ = 60.0;
  bool dead_;
  bool over_;
  unsigned int score_;
  unsigned int high_score_;
  int fps_;
  entt::registry registry_;
  HUD hud_;
  ResourceManager res_manager_;
  Window window_;
};

#endif  // ENTT_DINO_SRC_CORE_GAME_H_
