/**
 * @file      contexts.h
 * @brief     Contexts
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-11
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_CTX_CONTEXTS_H_
#define ENTT_DINO_SRC_CTX_CONTEXTS_H_

#include <SDL2/SDL_video.h>

#include <entt/entity/registry.hpp>

namespace contexts {

void SetWindowInfo(entt::registry* registry, SDL_Window* window);

}  // namespace contexts

#endif  // ENTT_DINO_SRC_CTX_CONTEXTS_H_
