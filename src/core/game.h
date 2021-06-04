/**
 * @file      game.h
 * @brief     Game logic and event loop.
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-02
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_CORE_GAME_H_
#define ENTT_DINO_SRC_CORE_GAME_H_

class Game
{
 public:
  Game();
  ~Game() = default;

  bool running();
  void Init();
  void Events();
  void Update();
  void Render();

 private:
  bool is_running_;
};

#endif /* ENTT_DINO_SRC_CORE_GAME_H_ */
