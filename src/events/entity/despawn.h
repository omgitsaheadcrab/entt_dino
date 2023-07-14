/**
 * @file      despawn.h
 * @brief     Entity despawn event
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-27
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_EVENTS_ENTITY_DESPAWN_H_
#define ENTT_DINO_SRC_EVENTS_ENTITY_DESPAWN_H_

#include <entt/entt.hpp>

namespace events {

namespace entity {

struct Despawn {
  entt::entity* entity;
};

}  // namespace entity

}  // namespace events

#endif  // ENTT_DINO_SRC_EVENTS_ENTITY_DESPAWN_H_
