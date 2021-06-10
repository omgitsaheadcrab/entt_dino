/**
 * @file      vec2d.h
 * @brief     Generic 2D Vector
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-08
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_CORE_VEC2D_H_
#define ENTT_DINO_SRC_CORE_VEC2D_H_

#include <cmath>
#include <cstdint>

template <class T>
struct vec2d {
  T x = 0;
  T y = 0;

  vec2d() : x(0), y(0) {}
  vec2d(T _x, T _y) : x(_x), y(_y) {}
  vec2d(const vec2d& v) : x(v.x), y(v.y) {}
  vec2d& operator=(const vec2d& v) = default;

  T mag() const { return T(std::sqrt(x * x + y * y)); }
};

typedef vec2d<int32_t> vi2d;
typedef vec2d<uint32_t> vu2d;
typedef vec2d<float> vf2d;
typedef vec2d<double> vd2d;

#endif  // ENTT_DINO_SRC_CORE_VEC2D_H_
