/**
 * @file      window.h
 * @brief     Class handling SDL window and renderer creation.
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-05-27
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_CORE_WINDOW_H_
#define ENTT_DINO_SRC_CORE_WINDOW_H_

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

class Window {
 public:
  Window() = delete;
  Window(const char kName[], const int kWindowWidth, const int kWindowHeight);
  ~Window();

  SDL_Event* event();
  SDL_Renderer* renderer();

 private:
  SDL_Event event_ {0};
  SDL_Window* window_;
  SDL_Renderer* renderer_;
};

#endif  // ENTT_DINO_SRC_CORE_WINDOW_H_
