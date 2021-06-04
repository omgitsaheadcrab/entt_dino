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
  Application() = delete;
  Application(const char* name, const int screen_width, const int screen_height,
              const double fps);
  ~Application();

  void Run();

 private:
  const char* name_;
  const int screen_width_;
  const int screen_height_;
  const double fps_;
  const double frame_delay_;
  SDL_Window* window_;
  SDL_Renderer* renderer_;
};

#endif /* ENTT_DINO_SRC_CORE_APP_H_ */
