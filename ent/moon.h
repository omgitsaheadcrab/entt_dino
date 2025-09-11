/**
 * @file      moon.h
 * @brief     Moon entity creation
 * @author    Tobias Backer Dirks <omgitsaheadcrab@gmail.com>
 * @date      2024-06-10
 * @copyright Copyright © 2024 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_ENT_MOON_H_
#define ENTT_DINO_SRC_ENT_MOON_H_

#include <entt/entity/registry.hpp>
#include "core/res_manager.h"

namespace entities {

namespace background {

// Create a moon entity at (x, y)
inline void CreateMoon(entt::registry* registry,
                       const omg::ResourceManager& res_manager,
                       double x, double y) {
  auto entity = registry->create();
  // Add identifier
  registry->emplace<components::identifiers::Moon>(entity);

  // Add transform (position and size)
  SDL_Rect rect;
  // Use the first frame of the "moon" sprite for size
  auto clips = res_manager.GetSpriteClips("moon", "moon");
  if (!clips.empty()) {
    rect = clips.front();
    rect.x = static_cast<int>(x);
    rect.y = static_cast<int>(y);
  } else {
    rect = {static_cast<int>(x), static_cast<int>(y), 32, 32}; // fallback size
  }
  registry->emplace<components::physics::Transform>(entity, rect);
}

}  // namespace background

}  // namespace entities

#endif  // ENTT_DINO_SRC_ENT_MOON_H_
