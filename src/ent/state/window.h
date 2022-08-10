/**
 * @file      window.h
 * @brief     Window state
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-10
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_ENT_STATE_WINDOW_H_
#define ENTT_DINO_SRC_ENT_STATE_WINDOW_H_

#include <SDL2/SDL_video.h>

#include <entt/entity/registry.hpp>

namespace entities {

void CreateWindowState(entt::registry* registry, SDL_Window* window);

}  // namespace entities

#endif  // ENTT_DINO_SRC_ENT_STATE_WINDOW_H_
