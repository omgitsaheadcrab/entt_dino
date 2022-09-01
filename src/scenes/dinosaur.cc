/**
 * @file      dinosaur.cc
 * @brief     Dinosaur scene
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-25
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#include "scenes/dinosaur.h"

#include <SDL2/SDL_events.h>

#include <memory>

#include "core/base_scene.h"
#include "core/colors.h"
#include "core/entity_manager.h"
#include "core/game.h"
#include "core/window.h"
#include "ctx/game_states.h"
#include "events/dino/dead.h"
#include "events/dino/running.h"
#include "sys/despawn.h"
#include "sys/move.h"
#include "sys/render.h"
#include "sys/score.h"
#include "sys/spawn.h"
#include "sys/states/dead.h"
#include "sys/states/running.h"
#include "sys/sync.h"

scenes::Dinosaur::Dinosaur() : omg::BaseScene("dinosaur") {}

void scenes::Dinosaur::Init() {
  entity_manager_.Init(game_);
  res_manager_->Init(game_->window().renderer());

  entity_manager_.AddRenderSystem(
      std::make_unique<systems::Render>(&game_->window()));

  entity_manager_.AddUpdateSystem(std::make_unique<systems::Spawn>());
  entity_manager_.AddUpdateSystem(std::make_unique<systems::Move>());
  entity_manager_.AddUpdateSystem(std::make_unique<systems::Score>());
  entity_manager_.AddUpdateSystem(std::make_unique<systems::Despawn>());
  entity_manager_.AddUpdateSystem(std::make_unique<systems::Sync>());

  entity_manager_.AddUpdateSystem(std::make_unique<systems::states::Dead>());
  entity_manager_.AddUpdateSystem(std::make_unique<systems::states::Running>());

  hud_->Init(entity_manager_.registry(), game_);
}

void scenes::Dinosaur::HandleEvents() {
  auto event = game_->window().event();
  SDL_PollEvent(&event);

  HandleBaseEvents(&event);

  switch (event.type) {
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
        case SDLK_SPACE:
          // Jump goes here
          break;
        case SDLK_d:
          entity_manager_.dispatcher()->trigger<events::dino::Dead>();
          break;
        case SDLK_r:
          entity_manager_.dispatcher()->trigger<events::dino::Running>();
          contexts::game_states::SetSpeed(entity_manager_.registry(), 0.15);
          contexts::game_states::SetScore(entity_manager_.registry(), 0);
          contexts::game_states::SetDistance(entity_manager_.registry(), 0);
          break;
        case SDLK_n:
          contexts::game_states::ToggleDark(entity_manager_.registry());
          break;
      }
      break;
    case SDL_KEYUP:
      switch (event.key.keysym.sym) {
        case SDLK_SPACE:
          break;
      }
      break;
    case SDL_MOUSEBUTTONDOWN:
      SDL_Point mouse_position;
      SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
      if (hud_->RetryClicked(mouse_position)) {
        entity_manager_.dispatcher()->trigger<events::dino::Running>();
        contexts::game_states::SetScore(entity_manager_.registry(), 0);
        contexts::game_states::SetSpeed(entity_manager_.registry(), 0.15);
      }
      break;
    default:
      break;
  }
}

void scenes::Dinosaur::Update(const double dt) {
  entity_manager_.OnUpdate(dt);
  hud_->Update();
}

void scenes::Dinosaur::Render(const double alpha) {
  auto color = colors::kBackgroundLight;
  if (contexts::game_states::GetDark(entity_manager_.registry())) {
    color = colors::kBackgroundDark;
  }

  game_->window().Clear(color);
  entity_manager_.OnRender(alpha);
  hud_->Draw();
  game_->window().Present();
}
