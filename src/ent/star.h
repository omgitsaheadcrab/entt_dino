/**
 * @file      star.h
 * @brief     Star entity creation
 * @author    Tobias Backer Dirks <omgitsaheadcrab@gmail.com>
 * @date      2024-06-10
 * @copyright Copyright © 2024 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_ENT_STAR_H_
#define ENTT_DINO_SRC_ENT_STAR_H_

#include <entt/entity/registry.hpp>
#include "core/res_manager.h"

namespace entities {

namespace background {

// Create a star entity at (x, y)
inline void CreateStar(entt::registry* registry,
                       const omg::ResourceManager& res_manager,
                       double x, double y) {
  auto entity = registry->create();
  // Add identifier
  registry->emplace<components::identifiers::Star>(entity);

  // Add transform (position and size)
  SDL_Rect rect;
  // Use the first frame of the "star" sprite for size
  auto clips = res_manager.GetSpriteClips("star", "star");
  if (!clips.empty()) {
    rect = clips.front();
    rect.x = static_cast<int>(x);
    rect.y = static_cast<int>(y);
  } else {
    rect = {static_cast<int>(x), static_cast<int>(y), 8, 8}; // fallback size
  }
  registry->emplace<components::physics::Transform>(entity, rect);
}

}  // namespace background

}  // namespace entities

#endif  // ENTT_DINO_SRC_ENT_STAR_H_
