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
#include "events/dino/ducking.h"
#include "events/dino/jumping.h"
#include "events/dino/running.h"
#include "events/game/restart.h"
#include "sys/collide.h"
#include "sys/despawn.h"
#include "sys/move.h"
#include "sys/render.h"
#include "sys/score.h"
#include "sys/spawn.h"
#include "sys/state.h"
#include "sys/sync.h"

scenes::Dinosaur::Dinosaur() : omg::BaseScene("dinosaur") {}

void scenes::Dinosaur::Init() {
  entity_manager_.Init(game_);

  entity_manager_.AddRenderSystem(
      std::make_unique<systems::Render>(&game_->window()));

  entity_manager_.AddUpdateSystem(std::make_unique<systems::Spawn>());
  entity_manager_.AddUpdateSystem(std::make_unique<systems::Despawn>());
  entity_manager_.AddUpdateSystem(std::make_unique<systems::Move>());
  entity_manager_.AddUpdateSystem(std::make_unique<systems::Score>());
  entity_manager_.AddUpdateSystem(std::make_unique<systems::Collide>());
  entity_manager_.AddUpdateSystem(std::make_unique<systems::State>());
  entity_manager_.AddUpdateSystem(std::make_unique<systems::Sync>());

  hud_.Init(entity_manager_.registry(), game_);
}

void scenes::Dinosaur::HandleEvents() {
  auto event = game_->window().event();
  SDL_PollEvent(&event);

  HandleBaseEvents(&event);

  switch (event.type) {
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
        case SDLK_SPACE:
          entity_manager_.dispatcher()->trigger<events::dino::JumpStart>();
          break;
        case SDLK_DOWN:
          if (contexts::game::GetState(entity_manager_.registry()).value ==
              "jumping") {
            entity_manager_.dispatcher()->trigger<events::dino::JumpDuck>();
          } else {
            entity_manager_.dispatcher()->trigger<events::dino::Ducking>();
          }
          break;
        case SDLK_n:
          contexts::game::ToggleDark(entity_manager_.registry());
          break;
        case SDLK_r:
          entity_manager_.dispatcher()->trigger<events::game::Restart>();
          break;
      }
      break;
    case SDL_KEYUP:
      switch (event.key.keysym.sym) {
        case SDLK_SPACE:
          entity_manager_.dispatcher()->trigger<events::dino::JumpEnd>();
          break;
        case SDLK_DOWN:
          if (contexts::game::GetState(entity_manager_.registry()).value ==
              "ducking") {
            entity_manager_.dispatcher()->trigger<events::dino::Running>();
          }
          break;
      }
      break;
    case SDL_MOUSEBUTTONDOWN:
      if (event.button.button == SDL_BUTTON_LEFT) {
        SDL_Point mouse_position = {event.button.x, event.button.y};
        if (hud_.RetryClicked(mouse_position)) {
          entity_manager_.dispatcher()->trigger<events::game::Restart>();
        }
      }
      break;
    case SDL_QUIT:
      game_->scene_manager().SetCurrentScene("closing_credits");
      break;
    default:
      break;
  }
}

void scenes::Dinosaur::Update(const double dt) {
  entity_manager_.OnUpdate(dt);
  hud_.Update();
}

void scenes::Dinosaur::Render(const double alpha) {
  auto color = colors::kBackgroundLight;
  if (contexts::game::GetDark(entity_manager_.registry())) {
    color = colors::kBackgroundDark;
  }

  game_->window().Clear(color);
  entity_manager_.OnRender(alpha);
  hud_.Draw();
  game_->window().Present();
}
