/**
 * @file      context.h
 * @brief     Contexts
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-12
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_CTX_CONTEXT_H_
#define ENTT_DINO_SRC_CTX_CONTEXT_H_

#include <cstdint>

#include <entt/entity/registry.hpp>

#include "comp/game/score.h"

namespace contexts {

template <typename T>
T Get(entt::registry* registry) {
  return registry->ctx().get<T>();
}

template <typename T>
bool GetBool(entt::registry* registry) {
  return registry->ctx().contains<T>();
}

template <typename T, typename U>
void Set(entt::registry* registry, const U u) {
  registry->ctx().insert_or_assign(T {u});
}

template <typename T>
void SetBool(entt::registry* registry, const bool over) {
  if (over) {
    registry->ctx().insert_or_assign(T {});
  } else {
    registry->ctx().erase<T>();
  }
}

template <typename T>
void ToggleBool(entt::registry* registry) {
  if (registry->ctx().contains<T>()) {
    registry->ctx().erase<T>();
  } else {
    registry->ctx().insert_or_assign(T {});
  }
}
}  // namespace contexts

#endif  // ENTT_DINO_SRC_CTX_CONTEXT_H_
