/**
 * @file      status.h
 * @brief     Status system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-24
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_SYS_STATUS_H_
#define ENTT_DINO_SRC_SYS_STATUS_H_

#include <cstdint>

#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>

#include "comp/state.h"

namespace systems {

void SetEntityStatus(entt::registry* registry, const entt::entity& entity,
                     components::State* state);

components::State GetEntityStatus(entt::registry* registry,
                                  const entt::entity& entity);

}  // namespace systems

#endif  // ENTT_DINO_SRC_SYS_STATUS_H_
