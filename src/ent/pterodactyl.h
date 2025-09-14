/**
 * @file      pterodactyl.h
 * @brief     Pterodactyl entity
 * @author    Tobias Backer Dirks <omgitsaheadcrab@gmail.com>
 * @date      2024-06-11
 * @copyright Copyright © 2024 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_ENT_PTERODACTYL_H_
#define ENTT_DINO_SRC_ENT_PTERODACTYL_H_

#include <entt/entity/registry.hpp>

#include "core/res_manager.h"

namespace entities {
namespace enemies {

// Create a pterodactyl entity at (x, y)
void CreatePterodactyl(entt::registry* registry,
                       const omg::ResourceManager& kResManager, int x, int y);

}  // namespace enemies
}  // namespace entities

#endif  // ENTT_DINO_SRC_ENT_PTERODACTYL_H_
