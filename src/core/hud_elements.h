/**
 * @file      hud_elements.h
 * @brief     HUD Elements
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2022-08-02
 * @copyright Copyright © 2022 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_CORE_HUD_ELEMENTS_H_
#define ENTT_DINO_SRC_CORE_HUD_ELEMENTS_H_

#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

#include <string>

namespace HUD {

struct Element {
  SDL_Rect position;
  SDL_Color color;
};

struct Text : Element {
  std::string str;
};

struct Icon : Element {
  SDL_Texture* texture;
  SDL_Rect clip;

  bool Clicked(const SDL_Point& mouse_pos);
};

}  // namespace HUD

#endif  // ENTT_DINO_SRC_CORE_HUD_ELEMENTS_H_
