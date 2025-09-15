/**
 * @file      animation.h
 * @brief     Animation component for entities
 * @author    (added by assistant)
 * @date      2025-09-15
 * @copyright Copyright © 2025 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_COMP_GRAPHICS_ANIMATION_H_
#define ENTT_DINO_SRC_COMP_GRAPHICS_ANIMATION_H_

#include <SDL2/SDL_rect.h>

#include <cstdint>
#include <vector>

namespace components {
namespace graphics {

struct Animation {
  std::vector<SDL_Rect> frames;
  std::size_t current_frame;
  uint32_t elapsed;
  uint32_t frame_duration;  // ms per frame

  Animation() : frames(), current_frame(0), elapsed(0), frame_duration(120) {}

  Animation(const std::vector<SDL_Rect>& frames_, std::size_t current_frame_,
            uint32_t elapsed_, uint32_t frame_duration_)
      : frames(frames_),
        current_frame(current_frame_),
        elapsed(elapsed_),
        frame_duration(frame_duration_) {}
};

}  // namespace graphics
}  // namespace components

#endif  // ENTT_DINO_SRC_COMP_GRAPHICS_ANIMATION_H_
