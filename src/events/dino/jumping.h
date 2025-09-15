/**
 * @file      jumping.h
 * @brief     Dino jumping event
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2025-09-15
 * @copyright Copyright © 2025 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_EVENTS_DINO_JUMPING_H_
#define ENTT_DINO_SRC_EVENTS_DINO_JUMPING_H_

namespace events {

namespace dino {

struct JumpStart {};

struct JumpEnd {};

struct JumpDuck {};

}  // namespace dino

}  // namespace events

#endif  // ENTT_DINO_SRC_EVENTS_DINO_JUMPING_H_
