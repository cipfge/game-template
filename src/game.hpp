#pragma once

#include <string>

struct GLFWwindow;

enum GameState
{
    GAME_MAIN_MENU,
    GAME_ACTIVE,
    GAME_PAUSED,
    GAME_OVER
};

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
    GameState m_state = GAME_MAIN_MENU;

    void input_event(int key, int scancode, int action, int mode);
    void resize_event(int width, int height);
    void render();
};
