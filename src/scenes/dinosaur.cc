/**
 * @file      dinosaur.cc
 * @brief     Dinosaur scene
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-25
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#include "scenes/dinosaur.h"

#include <SDL2/SDL_events.h>

#include <algorithm>
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

namespace {

// Helper to linearly interpolate between two Uint8 values
Uint8 lerp(Uint8 a, Uint8 b, float t) {
  return static_cast<Uint8>(a + t * (b - a));
}

// Helper to interpolate between two SDL_Color values
SDL_Color lerp_color(const SDL_Color& a, const SDL_Color& b, float t) {
  SDL_Color result;
  result.r = lerp(a.r, b.r, t);
  result.g = lerp(a.g, b.g, t);
  result.b = lerp(a.b, b.b, t);
  result.a = lerp(a.a, b.a, t);
  return result;
}

}  // namespace

void scenes::Dinosaur::StartBackgroundTransition(bool to_dark, int score) {
  transitioning_ = true;
  to_dark_ = to_dark;
  start_color_ = contexts::game::GetDark(entity_manager_.registry())
                     ? colors::kBackgroundDark
                     : colors::kBackgroundLight;
  end_color_ = to_dark ? colors::kBackgroundDark : colors::kBackgroundLight;
  transition_frame_ = 0;
  // Set the next threshold for transition
  last_score_for_transition_ =
      ((score / kTransitionPoints) + 1) * kTransitionPoints;
}

void scenes::Dinosaur::UpdateBackgroundTransition() {
  if (transitioning_) {
    float t = std::clamp(
        static_cast<float>(transition_frame_) / kTransitionFrames, 0.0f, 1.0f);
    current_color_ = lerp_color(start_color_, end_color_, t);

    transition_frame_++;
    if (transition_frame_ >= kTransitionFrames) {
      transitioning_ = false;
      current_color_ = end_color_;
      contexts::game::SetDark(entity_manager_.registry(), to_dark_);
    }
  } else {
    current_color_ = contexts::game::GetDark(entity_manager_.registry())
                         ? colors::kBackgroundDark
                         : colors::kBackgroundLight;
  }
}

scenes::Dinosaur::Dinosaur()
    : omg::BaseScene("dinosaur"),
      transitioning_(false),
      to_dark_(false),
      transition_frame_(0),
      last_transition_score_(0),
      last_score_for_transition_(0),
      just_restarted_(false) {}

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

  // Use colors from core/colors.h for background
  bool is_dark = contexts::game::GetDark(entity_manager_.registry());
  current_color_ = is_dark ? colors::kBackgroundDark : colors::kBackgroundLight;
  transitioning_ = false;
  transition_frame_ = 0;
  just_restarted_ = true;
  // Set initial threshold for transition
  int score = contexts::game::GetScore(entity_manager_.registry()).value;
  last_score_for_transition_ =
      ((score / kTransitionPoints) + 1) * kTransitionPoints;
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
        case SDLK_r:
          entity_manager_.dispatcher()->trigger<events::game::Restart>();
          just_restarted_ = true;
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
          just_restarted_ = true;
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

  int score = contexts::game::GetScore(entity_manager_.registry()).value;

  // On restart, reset transition state and next threshold
  if (just_restarted_) {
    bool is_dark = contexts::game::GetDark(entity_manager_.registry());
    current_color_ =
        is_dark ? colors::kBackgroundDark : colors::kBackgroundLight;
    transitioning_ = false;
    transition_frame_ = 0;
    last_transition_score_ = score;
    last_score_for_transition_ =
        ((score / kTransitionPoints) + 1) * kTransitionPoints;
    just_restarted_ = false;
  }

  // Check for transition trigger using explicit threshold
  if (!transitioning_ && score >= last_score_for_transition_) {
    StartBackgroundTransition(
        !contexts::game::GetDark(entity_manager_.registry()), score);
  }
  UpdateBackgroundTransition();
}

void scenes::Dinosaur::Render(const double alpha) {
  game_->window().Clear(current_color_);
  entity_manager_.OnRender(alpha);
  hud_.Draw();
  game_->window().Present();
}
