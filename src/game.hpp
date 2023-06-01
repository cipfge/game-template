#pragma once

#include "renderer.hpp"
#include <string>

struct GLFWwindow;

class Game
{
public:
    Game() = default;
    ~Game();

    bool init();
    void run();

private:
    GLFWwindow *m_window = nullptr;
    int m_window_width = 800;
    int m_window_height = 800;
    std::string m_window_title = "OpenGL Game";
    Renderer m_renderer;

    void input_event(int key, int scancode, int action, int mode);
    void resize_event(int width, int height);
    void render();
};
