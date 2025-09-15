/**
 * @file      res.cc
 * @brief     Locate resource directory
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2025-06-18
 * @copyright Copyright © 2025 Tobias Backer Dirks
 */

#include "util/res.h"

#include <SDL2/SDL_error.h>
#include <SDL2/SDL_filesystem.h>
#include <spdlog/spdlog.h>

#include <string>

/**
 * Return resource path.
 * @see Will Usher's `SDL2` Tutorials.
 */
std::string utils::GetResPath() {
  static std::string res_path;
  if (res_path.empty()) {
    auto base_path = SDL_GetBasePath();
    if (base_path) {
      res_path = base_path;
      SDL_free(base_path);
    } else {
      SPDLOG_ERROR("Failed to get base path: {}", SDL_GetError());
      return nullptr;
    }
    auto pos = res_path.rfind("bin");
    res_path = res_path.substr(0, pos) + "res/";
  }
  return res_path;
}
