/**
 * @file      sync.h
 * @brief     Synchronize physics to graphics
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-10
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_SYS_SYNC_H_
#define ENTT_DINO_SRC_SYS_SYNC_H_

#include <entt/entity/registry.hpp>

namespace systems {

namespace sync {

void Transforms(entt::registry* registry);

}  // namespace sync

}  // namespace systems

#endif  // ENTT_DINO_SRC_SYS_SYNC_H_
