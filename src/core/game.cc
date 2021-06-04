/**
 * @file      game.cc
 * @brief     Game logic and event loop.
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-02
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#include "core/game.h"

#include <SDL2/SDL.h>

bool Game::running() { return is_running_; }

void Game::Init() { is_running_ = true; }

void Game::Events() {
  SDL_Event event;

  SDL_PollEvent(&event);

  switch (event.type) {
    case SDL_QUIT:
      is_running_ = false;
      break;
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:  // Press ESC to quit
          is_running_ = false;
          break;
      }
      break;
    default:
      break;
  }
}

void Game::Update() {}

void Game::Render() {}
