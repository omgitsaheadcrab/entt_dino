/**
 * @file      animation.h
 * @brief     Animation component for entities
 * @author    (added by assistant)
 * @date      2024-06-12
 */

#ifndef ENTT_DINO_SRC_COMP_GRAPHICS_ANIMATION_H_
#define ENTT_DINO_SRC_COMP_GRAPHICS_ANIMATION_H_

#include <vector>
#include <cstdint>
#include <SDL2/SDL_rect.h>

namespace components {
namespace graphics {

struct Animation {
  std::vector<SDL_Rect> frames;
  std::size_t current_frame;
  uint32_t elapsed;
  uint32_t frame_duration; // ms per frame

  Animation() : current_frame(0), elapsed(0), frame_duration(120) {}
};

} // namespace graphics
} // namespace components

#endif // ENTT_DINO_SRC_COMP_GRAPHICS_ANIMATION_H_
