/**
 * @file      gravity.h
 * @brief     Gravity component
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-08
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_COMP_GRAVITY_H_
#define ENTT_DINO_SRC_COMP_GRAVITY_H_

#include "core/vec2d.h"

namespace components {

struct Gravity {
  vf2d force;
};

}  // namespace components

#endif /* ENTT_DINO_SRC_COMP_GRAVITY_H_ */
