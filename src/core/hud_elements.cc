/**
 * @file      hud_elements.cc
 * @brief     HUD Elements
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-02
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#include "core/hud_elements.h"

#include <SDL2/SDL_rect.h>

bool HUD::Icon::Clicked(const SDL_Point& mouse_pos) const {
  return (SDL_PointInRect(&mouse_pos, &(this)->position));
}
