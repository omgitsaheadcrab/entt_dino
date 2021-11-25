/**
 * @file      background.cc
 * @brief     Background system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-11-18
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */
#include "sys/background.h"

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

#include <iostream>
#include <set>
#include <string>

#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>

#include "comp/transform.h"
#include "ent/floor.h"

void systems::SpawnBackgroundElements(entt::registry* registry,
                                      SDL_Renderer* renderer,
                                      std::set<entt::entity>* bg_entities,
                                      SDL_Rect* bounds) {
  const auto view = registry->view<components::Transform>();
  if (bg_entities->empty()) {
    entt::entity new_last = entities::CreateFloor(registry, renderer, 0);
    bg_entities->emplace(new_last);
  }
  while (bg_entities->size() < 3) {
    entt::entity last = *bg_entities->rbegin();
    for (auto [entity, transform] : view.each()) {
      if (entity == last) {
        entt::entity new_last = entities::CreateFloor(
            registry, renderer, transform.position.x + transform.position.w);
        bg_entities->emplace(new_last);
      }
    }
  }
}
