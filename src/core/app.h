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
  Application(const char* kName, const int kScreen_width,
              const int kScreen_height, const double kFps);
  ~Application();

  void Run();

 private:
  const char* kName_;
  const int kScreen_width_;
  const int k_Screen_height_;
  const double kFps_;
  const double kFrame_Delay_;
  SDL_Window* window_;
  SDL_Renderer* renderer_;
};

#endif /* ENTT_DINO_SRC_CORE_APP_H_ */
