/**
 * @file      transform.h
 * @brief     Transform component
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-08
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_COMP_TRANSFORM_H_
#define ENTT_DINO_SRC_COMP_TRANSFORM_H_

#include "core/vec2d.h"

struct Transform {
  vf2d position;
  vf2d direction;
  vf2d scale;
};

#endif /* ENTT_DINO_SRC_COMP_TRANSFORM_H_ */
