/**
 * @file      base_scene.cc
 * @brief     Base scene
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2025-09-15
 * @copyright Copyright © 2025 Tobias Backer Dirks
 */

#include "core/base_scene.h"

#include <SDL2/SDL_events.h>

#include <string>

#include "core/game.h"

omg::BaseScene::BaseScene(const std::string& scene_name) { name_ = scene_name; }

std::string& omg::BaseScene::name() { return name_; }

void omg::BaseScene::HandleBaseEvents(const SDL_Event* event) {
  switch (event->type) {
    case SDL_QUIT:
      break;
    case SDL_WINDOWEVENT:
      break;
    case SDL_KEYDOWN:
      break;
    default:
      break;
  }
}

void omg::BaseScene::SetGame(omg::Game* game) {
  game_ = game;

  res_manager_ = &game->res_manager();
  scene_manager_ = &game->scene_manager();
  window_ = &game->window();
}
