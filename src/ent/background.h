/**
 * @file      background.h
 * @brief     Background entity
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-06-09
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_ENT_BACKGROUND_H_
#define ENTT_DINO_SRC_ENT_BACKGROUND_H_

#include <entt/entity/fwd.hpp>

struct SDL_Renderer;

void CreateBackground(entt::registry* registry, SDL_Renderer* renderer);

#endif /* ENTT_DINO_SRC_ENT_BACKGROUND_H_ */
