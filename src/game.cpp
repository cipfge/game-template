#include "game.hpp"
#include "logger.hpp"
#include <glad/glad.h>
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

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(m_window_width, m_window_height, m_window_title.c_str(), nullptr, nullptr);
    if (!m_window)
    {
        logger::error("Cannot create game window.");
        return false;
    }

    glfwSetWindowUserPointer(m_window, this);

    glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
    {
        Game *self = static_cast<Game*>(glfwGetWindowUserPointer(window));
        self->resize_event(width, height);
    });

    glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mode)
    {
        Game *self = static_cast<Game*>(glfwGetWindowUserPointer(window));
        self->input_event(key, scancode, action, mode);
    });

    glfwMakeContextCurrent(m_window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        logger::error("Cannot initialize OpenGL.");
        return false;
    }

    return true;
}

void Game::run()
{
    while (!glfwWindowShouldClose(m_window))
    {
        switch (m_state)
        {
        case GAME_MAIN_MENU: // TODO: main menu
        case GAME_ACTIVE: // TODO: gameplay
        case GAME_PAUSED: // TODO: pause menu
        case GAME_OVER: // TODO: game over
        default:
            render();
            break;
        }
    }
}

void Game::input_event(int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(m_window, GLFW_TRUE);
}

void Game::resize_event(int width, int height)
{
    m_window_width = width;
    m_window_height = height;
    glViewport(0, 0, m_window_width, m_window_height);
}

void Game::render()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(m_window);
    glfwPollEvents();
}
