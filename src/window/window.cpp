#include "window.hpp"

#include <stdexcept>
#include <iostream>

Window::Window(const int width, const int height, const std::string& name) : width(width), height(height), name(name), window(SDL_CreateWindow(name.c_str(), width, height, SDL_WINDOW_VULKAN), &SDL_DestroyWindow) {
    if (!window) {
        throw std::runtime_error(SDL_GetError());
    }
}

Window::~Window() {

}

SDL_Window* Window::getWindow() {
    return window.get();
}
