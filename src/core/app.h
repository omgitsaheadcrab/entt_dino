/**
 * @file      app.h
 * @brief     Main application handling SDL window creation.
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-05-27
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#ifndef SRC_CORE_APP_H_
#define SRC_CORE_APP_H_

#include <SDL2/SDL.h>

class Application {
 public:
  Application();
  ~Application();

  void run();

 private:
  static const int screen_width;
  static const int screen_height;
  SDL_Window *window;
  SDL_Renderer *renderer;
};

#endif /* SRC_CORE_APP_H_ */
