/**
 * @file      floor.h
 * @brief     Floor entity
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-09
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_ENT_FLOOR_H_
#define ENTT_DINO_SRC_ENT_FLOOR_H_

#include <SDL2/SDL_render.h>

#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>

namespace entities {

entt::entity CreateFloor(entt::registry* registry, SDL_Renderer* renderer,
                         const int xpos);

}  // namespace entities

#endif  // ENTT_DINO_SRC_ENT_FLOOR_H_
