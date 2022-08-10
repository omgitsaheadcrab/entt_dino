/**
 * @file      spawner.h
 * @brief     Spawner component
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-08
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_COMP_ATTRIBUTES_SPAWNER_H_
#define ENTT_DINO_SRC_COMP_ATTRIBUTES_SPAWNER_H_

#include <cstdint>

namespace components {

namespace attributes {

struct Spawner {
  uint32_t capacity;
  uint32_t count = 0;
};

}  // namespace attributes

}  // namespace components

#endif  // ENTT_DINO_SRC_COMP_ATTRIBUTES_SPAWNER_H_
