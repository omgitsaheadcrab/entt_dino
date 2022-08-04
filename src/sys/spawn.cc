/**
 * @file      spawn.cc
 * @brief     Spawn system
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-11-18
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */
#include "sys/spawn.h"

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

#include <set>

#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>

#include "comp/transform.h"
#include "core/res_manager.h"
#include "ent/cloud.h"
#include "ent/floor.h"

void systems::spawn::Clouds(entt::registry* registry,
                            const ResourceManager& res_manager,
                            std::set<entt::entity>* cloud_entities,
                            const SDL_Rect& bounds) {
  const auto view = registry->view<components::Transform>();
  if (cloud_entities->empty()) {
    auto cloud = entities::CreateCloud(registry, res_manager, bounds.w / 2);
    cloud_entities->emplace(cloud);
  }
  while (cloud_entities->size() < 2) {
    auto last = *cloud_entities->rbegin();
    for (auto [entity, transform] : view.each()) {
      if (entity == last) {
        auto new_last = entities::CreateCloud(
            registry, res_manager,
            transform.position.x + transform.position.w + bounds.w / 2);
        cloud_entities->emplace(new_last);
      }
    }
  }
}

void systems::spawn::Floors(entt::registry* registry,
                            const ResourceManager& res_manager,
                            std::set<entt::entity>* floor_entities,
                            const SDL_Rect& bounds) {
  const auto view = registry->view<components::Transform>();
  if (floor_entities->empty()) {
    auto floor = entities::CreateFloor(registry, res_manager, 0);
    floor_entities->emplace(floor);
  }
  while (floor_entities->size() < 3) {
    auto last = *floor_entities->rbegin();
    for (auto [entity, transform] : view.each()) {
      if (entity == last) {
        auto new_last = entities::CreateFloor(
            registry, res_manager, transform.position.x + transform.position.w);
        floor_entities->emplace(new_last);
      }
    }
  }
}
