/**
 * @file      offscreen.cc
 * @brief     Offscreen respawn system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-11-18
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#include "sys/offscreen.h"

#include <entt/entity/registry.hpp>

#include "comp/transform.h"
#include "ent/background.h"

void systems::Offscreen(entt::registry* registry, SDL_Renderer* renderer) {
  const auto view = registry->view<components::Transform>();
  for (auto [entity, transform] : view.each()) {
    if (transform.position.x <= -400) {
      registry->destroy(entity);
      entities::CreateBackground(registry, renderer, 800);
    }
  }
}
