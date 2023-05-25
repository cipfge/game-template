#pragma once

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
    int m_window_width = 1280;
    int m_window_height = 720;
    std::string m_window_title = "Snake";
};
