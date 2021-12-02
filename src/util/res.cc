/**
 * @file      res.cc
 * @brief     Locate resource directory
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-18
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#include "util/res.h"

#include <SDL2/SDL_error.h>
#include <SDL2/SDL_filesystem.h>
#include <SDL2/SDL_stdinc.h>
#include <spdlog/spdlog.h>

#include <cstring>
#include <memory>
#include <string>

#include "SDL_error.h"

/**
 * Return resource path.
 * @see Will Usher's `SDL2` Tutorials.
 */
const std::shared_ptr<char[]> utils::GetResPath(const std::string& image_name) {
  std::string res_path;
  char* base_path = SDL_GetBasePath();
  if (base_path) {
    res_path = base_path;
    SDL_free(base_path);
  } else {
    SPDLOG_ERROR("Failed to get base path: {}", SDL_GetError());
    return nullptr;
  }
  size_t pos = res_path.rfind("bin");
  res_path = res_path.substr(0, pos) + "res/" + image_name;

  // convert to c string as global constants should be char arrays
  std::shared_ptr<char[]> res_path_c(new char[res_path.size()]);
  std::snprintf(res_path_c.get(), res_path.size() + 1, "%s", res_path.c_str());
  return res_path_c;
}
