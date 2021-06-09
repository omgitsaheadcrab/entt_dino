/**
 * @file      game.cc
 * @brief     Game logic and event loop.
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-02
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#include "core/game.h"


struct SDL_Renderer;

bool Game::is_over() { return over_; }

void Game::Init(SDL_Renderer* renderer) {
  over_ = false;
}

void Game::HandleEvents() {
  SDL_Event event;

  SDL_PollEvent(&event);

  switch (event.type) {
    case SDL_QUIT:
      over_ = true;
      break;
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:  // Press ESC to quit
          over_ = true;
          break;
      }
      break;
    default:
      break;
  }
}

void Game::Update() {}

void Game::Render() {}
