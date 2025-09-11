/**
 * @file      star.h
 * @brief     Star entity
 * @author    Tobias Backer Dirks <omgitsaheadcrab@gmail.com>
 * @date      2024-06-10
 * @copyright Copyright © 2024 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_ENT_STAR_H_
#define ENTT_DINO_SRC_ENT_STAR_H_

#include <entt/entity/registry.hpp>

#include "core/res_manager.h"

namespace entities {
namespace background {

// Create a star entity at (x, y)
void CreateStar(entt::registry* registry,
                const omg::ResourceManager& kResManager, double x, double y);

}  // namespace background
}  // namespace entities

#endif  // ENTT_DINO_SRC_ENT_STAR_H_
