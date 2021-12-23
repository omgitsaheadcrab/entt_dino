/**
 * @file      background.h
 * @brief     Background system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-11-18
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_SYS_BACKGROUND_H_
#define ENTT_DINO_SRC_SYS_BACKGROUND_H_

#include <SDL2/SDL_rect.h>

#include <set>

#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>

#include "core/res_manager.h"

namespace systems {

void SpawnBackgroundElements(entt::registry* registry,
                             const ResourceManager& res_manager,
                             std::set<entt::entity>* cloud_entities,
                             std::set<entt::entity>* floor_entities,
                             const SDL_Rect& bounds);

}  // namespace systems

#endif  // ENTT_DINO_SRC_SYS_BACKGROUND_H_
