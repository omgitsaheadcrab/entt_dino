/**
 * @file      dino.h
 * @brief     Dino entity
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-11-27
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_ENT_DINO_H_
#define ENTT_DINO_SRC_ENT_DINO_H_

#include <entt/entity/registry.hpp>

#include "core/res_manager.h"

namespace entities {

namespace dino {

void Create(entt::registry* registry, const omg::ResourceManager& kResManager);
void SetDead(entt::registry* registry, const omg::ResourceManager& kResManager,
             const bool dead);

}  // namespace dino

}  // namespace entities

#endif  // ENTT_DINO_SRC_ENT_DINO_H_
