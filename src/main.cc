/**
 * @file      main.cc
 * @brief     Instantiate application and run.
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-05-27
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#include <spdlog/spdlog.h>

#include <exception>

#include "core/app.h"

int main(int argc, char *argv[]) {
  try {
#ifdef _DEBUG
    spdlog::set_level(spdlog::level::debug);
#endif  // _DEBUG
    Application app("entt_dino", 800, 244, 60.0);
    app.Run();
  } catch (std::exception &e) {
    SPDLOG_ERROR(e.what());
    return 1;
  }
  return 0;
}
