/**
 * @file      offscreen.h
 * @brief     Offscreen respawn system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-11-18
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_SYS_OFFSCREEN_H_
#define ENTT_DINO_SRC_SYS_OFFSCREEN_H_

#include <SDL2/SDL_render.h>

#include <entt/entity/registry.hpp>

namespace systems {

void Offscreen(entt::registry* registry, SDL_Renderer* renderer);

}  // namespace systems

#endif  // ENTT_DINO_SRC_SYS_OFFSCREEN_H_
