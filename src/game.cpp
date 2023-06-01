#include "game.hpp"
#include "logger.hpp"
#include "shader.hpp"
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

    glViewport(0, 0, m_window_width, m_window_height);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (!m_renderer.init(m_window_width, m_window_height))
        return false;

    logger::info("OpenGL initialized:");
    logger::info("\tVendor: %s", glGetString(GL_VENDOR));
    logger::info("\tRenderer: %s", glGetString(GL_RENDERER));
    logger::info("\tVersion: %s", glGetString(GL_VERSION));

    return true;
}

void Game::run()
{
    while (!glfwWindowShouldClose(m_window))
    {
        glfwPollEvents();
        render();
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
    m_renderer.resize(m_window_width, m_window_height);

    glViewport(0, 0, m_window_width, m_window_height);
}

void Game::render()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    m_renderer.render_text("Text", 20.0f, 20.f, 1.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    glfwSwapBuffers(m_window);
}
