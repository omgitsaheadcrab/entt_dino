/**
 * @file      random.h
 * @brief     Random number generation
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-18
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_CORE_RANDOM_H_
#define ENTT_DINO_SRC_CORE_RANDOM_H_

namespace utils {

int uniform_random(const int lower_bound, const int upper_bound);

}  // namespace utils

#endif  // ENTT_DINO_SRC_CORE_RANDOM_H_
