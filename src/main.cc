/**
 * @file      main.cc
 * @brief     Instantiate game and run
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-05-27
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#include <spdlog/spdlog.h>

#include <iostream>

#include "core/game.h"

int main(int argc, char* argv[]) {
#ifdef _DEBUG
  spdlog::set_level(spdlog::level::debug);
#endif  // _DEBUG
  omg::Game game(800, 244);
  game.Run();
  std::cout << "Veni. Vidi. Reverti.\n";
  return 0;
}
