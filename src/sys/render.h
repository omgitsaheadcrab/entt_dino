/**
 * @file      render.h
 * @brief     Render system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-13
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_SYS_RENDER_H_
#define ENTT_DINO_SRC_SYS_RENDER_H_

#include <SDL2/SDL_render.h>

#include <entt/entity/registry.hpp>

namespace systems {

void Render(SDL_Renderer* renderer, entt::registry* registry);

}  // namespace systems

#endif  // ENTT_DINO_SRC_SYS_RENDER_H_
