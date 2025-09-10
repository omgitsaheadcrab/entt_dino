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
#include <algorithm>

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

namespace {

// Helper to linearly interpolate between two Uint8 values
Uint8 lerp(Uint8 a, Uint8 b, float t) {
  return static_cast<Uint8>(a + t * (b - a));
}

} // namespace

scenes::Dinosaur::Dinosaur()
    : omg::BaseScene("dinosaur"),
      transitioning_(false),
      to_dark_(false),
      transition_frames_(60),
      transition_frame_(0),
      last_transition_score_(0)
{}

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

  // Initialize color state
  current_color_ = colors::kBackgroundLight;
  last_transition_score_ = 0;
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
          if (contexts::game::GetState(entity_manager_.registry())->value ==
              "jumping") {
            entity_manager_.dispatcher()->trigger<events::dino::JumpDuck>();
          } else {
            entity_manager_.dispatcher()->trigger<events::dino::Ducking>();
          }
          break;
        case SDLK_n:
          // Manual toggle (for debug/testing)
          contexts::game::ToggleDark(entity_manager_.registry());
          break;
        case SDLK_r:
          entity_manager_.dispatcher()->trigger<events::game::Restart>();
          break;
        case SDLK_ESCAPE:
          game_->scene_manager().SetCurrentScene("closing_credits");
          break;
      }
      break;
    case SDL_KEYUP:
      switch (event.key.keysym.sym) {
        case SDLK_SPACE:
          entity_manager_.dispatcher()->trigger<events::dino::JumpEnd>();
          break;
        case SDLK_DOWN:
          if (contexts::game::GetState(entity_manager_.registry())->value ==
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

  // Get current score (replace with your actual score retrieval if needed)
  int score = 0;
  // Try to get score from registry context (pointer access)
  if (entity_manager_.registry()->ctx().contains<int>()) {
    score = entity_manager_.registry()->ctx().get<int>();
  }

  // Check for transition trigger every 200 points
  if (!transitioning_ && (score / 200 > last_transition_score_ / 200)) {
    transitioning_ = true;
    to_dark_ = !contexts::game::GetDark(entity_manager_.registry());
    start_color_ = current_color_;
    end_color_ = to_dark_ ? colors::kBackgroundDark : colors::kBackgroundLight;
    transition_frame_ = 0;
    last_transition_score_ = score;
  }

  // If transitioning, update current_color_
  if (transitioning_) {
    float t = std::clamp(static_cast<float>(transition_frame_) / transition_frames_, 0.0f, 1.0f);
    current_color_.r = lerp(start_color_.r, end_color_.r, t);
    current_color_.g = lerp(start_color_.g, end_color_.g, t);
    current_color_.b = lerp(start_color_.b, end_color_.b, t);
    current_color_.a = lerp(start_color_.a, end_color_.a, t);
    transition_frame_++;
    if (transition_frame_ >= transition_frames_) {
      transitioning_ = false;
      current_color_ = end_color_;
      // Actually toggle dark mode in the registry
      contexts::game::SetDark(entity_manager_.registry(), to_dark_);
    }
  } else {
    // Not transitioning, use current mode
    current_color_ = contexts::game::GetDark(entity_manager_.registry())
        ? colors::kBackgroundDark
        : colors::kBackgroundLight;
  }
}

void scenes::Dinosaur::Render(const double alpha) {
  // Use current_color_ for background
  game_->window().Clear(current_color_);
  entity_manager_.OnRender(alpha);
  hud_.Draw();
  game_->window().Present();
}
