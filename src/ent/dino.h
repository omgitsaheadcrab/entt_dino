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

#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>

#include "core/res_manager.h"

namespace entities {

entt::entity CreateDino(entt::registry* registry,
                        const ResourceManager& res_manager,
                        const SDL_Rect& bounds);

}  // namespace entities

#endif  // ENTT_DINO_SRC_ENT_DINO_H_
