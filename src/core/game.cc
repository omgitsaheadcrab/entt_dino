/**
 * @file      game.cc
 * @brief     Game logic and event loop.
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-02
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#include "core/game.h"

#include <SDL2/SDL.h>

#include "ent/background.h"
#include "sys/despawn.h"
#include "sys/movement.h"
#include "sys/render.h"

bool Game::is_over() { return over_; }

void Game::Init(SDL_Renderer* renderer, const int kWindow_width,
                const int kWindow_height) {
  over_ = false;
  bounds_ = SDL_Rect {0, 0, kWindow_width, kWindow_height};
  for (auto i = 0; i < 3; ++i) {
    entities::CreateBackground(&registry_, renderer, i * bounds_.w / 2);
  }
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

void Game::Update(SDL_Renderer* renderer) {
  systems::Move(&registry_);
  systems::Despawn(&registry_);
}

void Game::Render(SDL_Renderer* renderer) {
  SDL_SetRenderDrawColor(renderer, 239, 239, 239, 255);
  SDL_RenderClear(renderer);
  systems::Render(renderer, &registry_);
  SDL_RenderPresent(renderer);
}
