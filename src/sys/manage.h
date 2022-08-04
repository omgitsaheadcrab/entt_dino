/**
 * @file      manage.h
 * @brief     Entity state system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-04
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_SYS_MANAGE_H_
#define ENTT_DINO_SRC_SYS_MANAGE_H_

#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>

#include "comp/state.h"

namespace systems {

namespace manage {

void SetEntityState(entt::registry* registry, const entt::entity& entity,
                    components::State* state);

components::State GetEntityState(entt::registry* registry,
                                 const entt::entity& entity);

}  // namespace manage

}  // namespace systems

#endif  // ENTT_DINO_SRC_SYS_MANAGE_H_
