/**
 * @file      spawn.cc
 * @brief     Spawn system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-11-18
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */
#include "sys/spawn.h"

#include <chrono>
#include <random>

#include "comp/identifiers/cloud.h"
#include "comp/identifiers/enemy.h"
#include "comp/identifiers/floor.h"
#include "comp/identifiers/moon.h"
#include "comp/identifiers/star.h"
#include "comp/physics/transform.h"
#include "core/game.h"
#include "ctx/game_states.h"
#include "ctx/graphics.h"
#include "ent/cactii.h"
#include "ent/cloud.h"
#include "ent/dino.h"
#include "ent/floor.h"
#include "ent/moon.h"
#include "ent/star.h"
#include "events/entity/despawn.h"
#include "events/game/restart.h"
#include "util/random.h"

namespace {
// Increased min/max spacing for clouds to reduce clustering
constexpr int kCloudMinSpacing = 300;
constexpr int kCloudMaxSpacing = 600;

// Star spawn parameters
constexpr int kMinStars = 1;
constexpr int kMaxStars = 3;
constexpr int kStarMinY = 20;
constexpr int kStarMaxY = 80;
constexpr int kStarMinX = 50;
constexpr int kStarMaxX = 750;
}  // namespace

void systems::Spawn::OnInit() {
  dispatcher_->sink<events::game::Restart>()
      .connect<&systems::Spawn::OnRestart>(this);

  entities::dino::Create(registry_, game_->res_manager());
  Cactii();
  Clouds();
  Floors();
  MoonAndStars();
}

void systems::Spawn::Update(const double dt) {
  Cactii();
  Clouds();
  Floors();
  MoonAndStars();
}

void systems::Spawn::Cactii() {
  const auto kCactiiView = registry_->view<components::physics::Transform,
                                           components::identifiers::Enemy>();
  const auto& kBounds = contexts::graphics::GetBounds(registry_);
  constexpr auto kMaxCount = 3;

  auto count = kCactiiView.size_hint();
  if (count == 0) {
    double pos = kBounds.position.w + kBounds.position.w / 5.0;
    entities::enemies::CreateCactii(registry_, game_->res_manager(), pos);
    count++;
    while (count < kMaxCount) {
      pos += 2 * kBounds.position.w / 5.0;
      entities::enemies::CreateCactii(registry_, game_->res_manager(), pos);
      ++count;
    }
  }

  kCactiiView.each([&](auto entity, const auto& kTransform) {
    if (kTransform.position.x <= -kTransform.position.w) {
      dispatcher_->trigger(events::entity::Despawn {&entity});
      entities::enemies::CreateCactii(registry_, game_->res_manager(),
                                      kBounds.position.w);
      count++;
    }
  });
}

void systems::Spawn::Clouds() {
  const auto kCloudView = registry_->view<components::physics::Transform,
                                          components::identifiers::Cloud>();
  const auto& kBounds = contexts::graphics::GetBounds(registry_);
  constexpr auto kMaxCount = 2;

  auto count = kCloudView.size_hint();

  // Static variable to track next cloud spawn position
  static int next_cloud_spawn_x = kBounds.position.w / 4;

  if (count == 0) {
    // First cloud
    entities::background::CreateCloud(registry_, game_->res_manager(),
                                      next_cloud_spawn_x);
    ++count;

    // Spawn up to kMaxCount clouds with random spacing
    while (count < kMaxCount) {
      int spacing = utils::UniformRandom(kCloudMinSpacing, kCloudMaxSpacing);
      next_cloud_spawn_x += spacing;
      entities::background::CreateCloud(registry_, game_->res_manager(),
                                        next_cloud_spawn_x);
      ++count;
    }
  }

  kCloudView.each([&](auto entity, const auto& kTransform) {
    if (kTransform.position.x <= -kTransform.position.w) {
      // When a cloud despawns, spawn a new one at a random distance ahead
      int spacing = utils::UniformRandom(kCloudMinSpacing, kCloudMaxSpacing);
      int kPos = static_cast<int>(kTransform.position.x + kTransform.position.w +
                                  spacing + kBounds.position.w);
      entities::background::CreateCloud(registry_, game_->res_manager(), kPos);
      dispatcher_->trigger(events::entity::Despawn {&entity});
      count++;
    }
  });
}

void systems::Spawn::Floors() {
  const auto kFloorView = registry_->view<components::physics::Transform,
                                          components::identifiers::Floor>();
  constexpr auto kMaxCount = 3;

  auto current_pos = 0;
  auto width = 0;
  auto count = kFloorView.size_hint();

  if (count == 0) {
    entities::background::CreateFloor(registry_, game_->res_manager(), 0);
    ++count;
    kFloorView.each([&](const auto& kTransform) {
      current_pos = kTransform.position.x + kTransform.position.w;
      width = kTransform.position.w;
    });

    while (count < kMaxCount) {
      entities::background::CreateFloor(registry_, game_->res_manager(),
                                        current_pos);
      ++count;
      current_pos += width;
    }
  }

  kFloorView.each([&](auto entity, const auto& kTransform) {
    if (kTransform.position.x <= -kTransform.position.w) {
      const auto kPos =
          kTransform.position.x + (kTransform.position.w * kMaxCount);

      entities::background::CreateFloor(registry_, game_->res_manager(), kPos);
      dispatcher_->trigger(events::entity::Despawn {&entity});
      count++;
    }
  });
}

void systems::Spawn::MoonAndStars() {
  // Only spawn during "night"
  bool is_dark = contexts::game::GetDark(registry_);
  const auto& kBounds = contexts::graphics::GetBounds(registry_);

  // Moon: only one should exist
  auto moon_view = registry_->view<components::identifiers::Moon>();
  if (is_dark) {
    bool moon_exists = false;
    for (auto entity : moon_view) {
      moon_exists = true;
      break;
    }
    if (!moon_exists) {
      // Random moon position (upper right quadrant)
      int moon_x = utils::UniformRandom(static_cast<int>(kBounds.position.w * 0.6),
                                        static_cast<int>(kBounds.position.w * 0.85));
      int moon_y = utils::UniformRandom(10, static_cast<int>(kBounds.position.h * 0.3));
      entities::background::CreateMoon(registry_, game_->res_manager(), moon_x,
                                       moon_y);
    }
  } else {
    // Despawn moon if present
    for (auto entity : moon_view) {
      dispatcher_->trigger(events::entity::Despawn {&entity});
    }
  }

  // Stars: random number, random positions, only during night
  auto star_view = registry_->view<components::identifiers::Star>();
  if (is_dark) {
    bool stars_exist = false;
    for (auto entity : star_view) {
      stars_exist = true;
      break;
    }
    if (!stars_exist) {
      int star_count = utils::UniformRandom(kMinStars, kMaxStars);
      for (int i = 0; i < star_count; ++i) {
        int star_x = utils::UniformRandom(kStarMinX, kStarMaxX);
        int star_y = utils::UniformRandom(kStarMinY, kStarMaxY);
        entities::background::CreateStar(registry_, game_->res_manager(),
                                         star_x, star_y);
      }
    }
  } else {
    // Despawn stars if present
    for (auto entity : star_view) {
      dispatcher_->trigger(events::entity::Despawn {&entity});
    }
  }
}

void systems::Spawn::OnRestart() {
  entities::dino::Create(registry_, game_->res_manager());
}
