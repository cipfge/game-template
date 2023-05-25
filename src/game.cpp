#include "game.hpp"
#include "logger.hpp"
#include <GLFW/glfw3.h>

Game::~Game()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

bool Game::init()
{
    if (!glfwInit())
    {
        logger::error("Cannot initialize GLFW.");
        return false;
    }

    m_window = glfwCreateWindow(m_window_width, m_window_height, m_window_title.c_str(), nullptr, nullptr);
    if (!m_window)
    {
        logger::error("Cannot create game window.");
        return false;
    }

    return true;
}

void Game::run()
{
    while (!glfwWindowShouldClose(m_window))
    {
    }
}
