/**
 * @file      game.h
 * @brief     Game logic and event loop.
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-02
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_CORE_GAME_H_
#define ENTT_DINO_SRC_CORE_GAME_H_

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

#include <set>

#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>

class Game {
 public:
  Game() = default;
  ~Game() = default;

  bool is_over();
  void Init(SDL_Renderer* renderer, const int kWindow_width,
            const int kWindow_height);
  void HandleEvents();
  void Update(SDL_Renderer* renderer);
  void Render(SDL_Renderer* renderer);

 private:
  unsigned int base_speed_;
  std::set<entt::entity> bg_entities_;
  SDL_Rect bounds_;
  bool over_;
  entt::registry registry_;
};

#endif  // ENTT_DINO_SRC_CORE_GAME_H_
