/**
 * @file      graphics.h
 * @brief     Graphics contexts
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-11
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_CTX_GRAPHICS_H_
#define ENTT_DINO_SRC_CTX_GRAPHICS_H_

#include <SDL2/SDL_video.h>

#include <cstdint>

#include <entt/entity/registry.hpp>

#include "comp/graphics/bounds.h"
#include "comp/graphics/fps.h"
#include "ctx/context.h"

namespace contexts {

namespace graphics {

constexpr auto GetFPS = &contexts::Get<components::graphics::FPS>;
constexpr auto SetFPS =
    &contexts::Set<components::graphics::FPS, const uint32_t>;

constexpr auto GetBounds = &contexts::Get<components::graphics::Bounds>;
void SetBounds(entt::registry* registry, SDL_Window* window);

}  // namespace graphics

}  // namespace contexts

#endif  // ENTT_DINO_SRC_CTX_GRAPHICS_H_
