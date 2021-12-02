/**
 * @file      res.h
 * @brief     Locate resource directory
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-18
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_UTIL_RES_H_
#define ENTT_DINO_SRC_UTIL_RES_H_

#include <memory>
#include <string>

namespace utils {

const std::shared_ptr<char[]> GetResPath(const std::string& image_name);

}  // namespace utils

#endif  // ENTT_DINO_SRC_UTIL_RES_H_
