/**
 * @file      window.cc
 * @brief     Class handling SDL window and renderer creation.
 * @author    Tobias Backer Dirks <omgitsaheadcrab[at]gmail.com>
 * @date      2021-05-27
 * @copyright Copyright © 2021 Tobias Backer Dirks
 */

#include "core/window.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_ttf.h>

#include <string>

Window::Window(const std::string& kName, const int kWindowWidth,
               const int kWindowHeight)
    : window_ {SDL_CreateWindow(kName.c_str(), SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, kWindowWidth,
                                kWindowHeight, SDL_WINDOW_RESIZABLE)},
      renderer_ {SDL_CreateRenderer(
          window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE)},
      bounds_ {0, 0, kWindowWidth, kWindowHeight} {
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
  TTF_Init();
  SDL_RenderSetLogicalSize(renderer_, kWindowWidth, kWindowHeight);
}

Window::~Window() {
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);
  TTF_Quit();
  SDL_Quit();
}

const SDL_Rect& Window::bounds() { return bounds_; }

SDL_Event& Window::event() { return event_; }

SDL_Renderer* Window::renderer() { return renderer_; }
