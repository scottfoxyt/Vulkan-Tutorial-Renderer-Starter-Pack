#include "application.hpp"

#include <stdexcept>

Application::Application() : window(width, height, name) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw std::runtime_error(SDL_GetError());
    }
}

Application::~Application() {
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

void Application::run() {
    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }
    }
}