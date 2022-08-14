/**
 * @file      context.h
 * @brief     Contexts
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-12
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_CTX_CONTEXT_H_
#define ENTT_DINO_SRC_CTX_CONTEXT_H_

#include <entt/entity/registry.hpp>

#include "comp/game_states/score.h"

namespace contexts {

template <typename T>
T get(entt::registry* registry) {
  return registry->ctx().get<T>();
}

template <typename T>
bool get_bool(entt::registry* registry) {
  return registry->ctx().contains<T>();
}

template <typename T, typename U>
void set(entt::registry* registry, U u) {
  registry->ctx().insert_or_assign(T {u});
}

template <typename T>
void set_bool(entt::registry* registry, const bool over) {
  if (over) {
    registry->ctx().insert_or_assign(T {});
  } else {
    registry->ctx().erase<T>();
  }
}

}  // namespace contexts

#endif  // ENTT_DINO_SRC_CTX_CONTEXT_H_
