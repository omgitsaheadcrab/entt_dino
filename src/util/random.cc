/**
 * @file      random.cc
 * @brief     Random number generation
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2025-09-15
 * @copyright Copyright © 2025 Tobias Backer Dirks
 */

#include "util/random.h"

#include <random>

namespace {

std::mt19937 randgen(std::random_device {}());

}  // namespace

int utils::UniformRandom(const int lower_bound, const int upper_bound) {
  std::uniform_int_distribution<int> uniform_distribution(lower_bound,
                                                          upper_bound);
  return uniform_distribution(randgen);
}
