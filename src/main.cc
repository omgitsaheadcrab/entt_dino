/**
 * @file      main.cc
 * @brief     Instantiate application and run.
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-05-27
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#include <exception>
#include <iostream>

#include "core/app.h"

int main(int argc, char *argv[]) {
  try {
    Application app("entt_dino", 800, 244, 60.0);
    app.run();
  } catch (std::exception &e) {
    std::cout << e.what() << "\n";
    return 1;
  }
  return 0;
}
