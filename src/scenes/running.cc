/**
 * @file      running.cc
 * @brief     Running scene
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-25
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#include "scenes/running.h"

#include <memory>

#include "SDL_events.h"
#include "core/base_scene.h"
#include "core/colors.h"
#include "core/entity_manager.h"
#include "core/game.h"
#include "core/window.h"
#include "ctx/game_states.h"
#include "ctx/graphics.h"
#include "ent/dino.h"
#include "sys/despawn.h"
#include "sys/move.h"
#include "sys/render.h"
#include "sys/score.h"
#include "sys/spawn.h"
#include "sys/sync.h"

scenes::Running::Running() : omg::BaseScene("running") {}

void scenes::Running::Init() {
  entity_manager_.Init(game_);

  contexts::graphics::SetFPS(entity_manager_.registry(), 0);
  contexts::game_states::SetSpeed(entity_manager_.registry(), 0.15);
  contexts::game_states::SetScore(entity_manager_.registry(), 0);
  contexts::game_states::SetHighscore(entity_manager_.registry(), 0);
  contexts::graphics::SetBounds(entity_manager_.registry(),
                                game_->window().window());

  res_manager_->Init(game_->window().renderer());
  hud_->Init(entity_manager_.registry(), game_->window().renderer(),
             res_manager_);

  entity_manager_.AddUpdateSystem(std::make_unique<systems::Spawn>());
  entity_manager_.AddUpdateSystem(std::make_unique<systems::Move>());
  entity_manager_.AddUpdateSystem(std::make_unique<systems::Score>());
  entity_manager_.AddUpdateSystem(std::make_unique<systems::Despawn>());
  entity_manager_.AddUpdateSystem(std::make_unique<systems::Sync>());

  entity_manager_.AddRenderSystem(
      std::make_unique<systems::Render>(&game_->window()));
}

void scenes::Running::HandleEvents() {
  auto event = game_->window().event();

  SDL_PollEvent(&event);

  HandleBaseEvents(&event);

  uint32_t score, high_score;

  switch (event.type) {
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
        case SDLK_SPACE:
          // Jump goes here
          break;
        case SDLK_d:
          entities::dino::SetDead(entity_manager_.registry(), *res_manager_,
                                  true);
          score =
              contexts::game_states::GetScore(entity_manager_.registry()).value;
          high_score =
              contexts::game_states::GetHighscore(entity_manager_.registry())
                  .value;
          high_score = score > high_score ? score : high_score;
          contexts::game_states::SetHighscore(entity_manager_.registry(),
                                              high_score);
          break;
        case SDLK_r:
          entities::dino::SetDead(entity_manager_.registry(), *res_manager_,
                                  false);
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
        entities::dino::SetDead(entity_manager_.registry(), *res_manager_,
                                false);
        contexts::game_states::SetScore(entity_manager_.registry(), 0);
        contexts::game_states::SetSpeed(entity_manager_.registry(), 0.15);
      }
      break;
    default:
      break;
  }
}

void scenes::Running::Update(const double dt) {
  entity_manager_.OnUpdate(dt);
  hud_->Update(entity_manager_.registry());
}

void scenes::Running::Render(const double alpha) {
  auto color = colors::kBackgroundLight;
  if (contexts::game_states::GetDark(entity_manager_.registry())) {
    color = colors::kBackgroundDark;
  }
  game_->window().Clear(color);

  entity_manager_.OnRender(alpha);

  hud_->Draw(entity_manager_.registry());
  game_->window().Present();
}
