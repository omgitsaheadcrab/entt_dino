/**
 * @file      cloud.h
 * @brief     Cloud entity
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-11-25
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_ENT_CLOUD_H_
#define ENTT_DINO_SRC_ENT_CLOUD_H_

#include <SDL2/SDL_render.h>

#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>

namespace entities {

entt::entity CreateCloud(entt::registry* registry, SDL_Renderer* renderer,
                         const int xpos);

}  // namespace entities

#endif  // ENTT_DINO_SRC_ENT_CLOUD_H_
