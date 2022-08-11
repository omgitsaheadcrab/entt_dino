/**
 * @file      str.h
 * @brief     String utils
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-11
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_UTIL_STR_H_
#define ENTT_DINO_SRC_UTIL_STR_H_

#include <cstdint>
#include <string>

namespace utils {

std::string ToStringZeroPad(const uint32_t num, const uint32_t padding);

}  // namespace utils

#endif  // ENTT_DINO_SRC_UTIL_STR_H_
