/**
 * @file      general.h
 * @brief     General contexts
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-11
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_CTX_GENERAL_H_
#define ENTT_DINO_SRC_CTX_GENERAL_H_

#include <SDL2/SDL_video.h>

#include <cstdint>

#include <entt/entity/registry.hpp>

#include "comp/graphics/fps.h"
#include "comp/graphics/window_info.h"
#include "ctx/context.h"

namespace contexts {

constexpr auto GetFPS = &contexts::Get<components::graphics::FPS>;
constexpr auto GetWindowInfo = &contexts::Get<components::graphics::WindowInfo>;

constexpr auto SetFPS =
    &contexts::Set<components::graphics::FPS, const uint32_t>;
void SetWindowInfo(entt::registry* registry, SDL_Window* window);

}  // namespace contexts

#endif  // ENTT_DINO_SRC_CTX_GENERAL_H_
