#pragma once

#include "window.hpp"

#include <string>

class Application {
public:
    Application();
    ~Application();

    void run();

private:
    int width = 1280;
    int height = 720;
    std::string name = "Unnamed Block Game";

    Window window;
};