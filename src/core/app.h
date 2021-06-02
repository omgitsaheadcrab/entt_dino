/**
 * @file      app.h
 * @brief     Main application handling SDL window creation.
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-05-27
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#ifndef ENTT_DINO_SRC_CORE_APP_H_
#define ENTT_DINO_SRC_CORE_APP_H_

#include <SDL2/SDL.h>

class Application {
 public:
  Application();
  ~Application();

  void run();

 private:
  static const int screen_width_;
  static const int screen_height_;
  SDL_Window *window_;
  SDL_Renderer *renderer_;
};

#endif /* ENTT_DINO_SRC_CORE_APP_H_ */
