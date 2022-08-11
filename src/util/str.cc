/**
 * @file      str.cc
 * @brief     String utils
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-11
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#include "util/str.h"

#include <cstdint>
#include <string>

std::string utils::ToStringZeroPad(const uint32_t num, const uint32_t padding) {
  auto s = std::to_string(num);
  uint32_t number_of_zeros = padding - s.length();
  s.insert(0, number_of_zeros, '0');
  return s;
}
