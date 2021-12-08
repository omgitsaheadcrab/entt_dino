/**
 * @file      dino.h
 * @brief     Dino entity
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-11-27
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_ENT_DINO_H_
#define ENTT_DINO_SRC_ENT_DINO_H_

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>

namespace entities {

entt::entity CreateDino(entt::registry* registry, SDL_Renderer* renderer,
                        const SDL_Rect& bounds);

}  // namespace entities

#endif  // ENTT_DINO_SRC_ENT_DINO_H_
