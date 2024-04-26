#pragma once

#include <memory>
#include <SDL3/SDL.h>

#include <string>

class Window {
public:
    Window(int width, int height, const std::string& name);
    ~Window();

    SDL_Window* getWindow();
private:
    const int width;
    const int height;
    const std::string name;
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window;
};
