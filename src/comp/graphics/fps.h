/**
 * @file      fps.h
 * @brief     Frame rate component
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-11
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_COMP_GRAPHICS_FPS_H_
#define ENTT_DINO_SRC_COMP_GRAPHICS_FPS_H_

#include <cstdint>

namespace components {

namespace graphics {

struct FPS {
  uint32_t value;
};

}  // namespace graphics

}  // namespace components

#endif  // ENTT_DINO_SRC_COMP_GRAPHICS_FPS_H_
