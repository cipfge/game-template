#pragma once

#include "shader.hpp"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <map>
#include <string>

struct Character
{
    GLuint texture_id;
    glm::ivec2 size;
    glm::ivec2 bearing;
    GLuint advance;
};

class Renderer
{
public:
    Renderer();
    ~Renderer();

    bool init();
    void cleanup();

    void render_text(const std::string &text, float x, float y, float scale, glm::vec3 color);

private:
    Shader m_text_shader;
    std::map<char, Character> m_characters;
    GLuint m_vao;
    GLuint m_vbo;

    bool load_font(const std::string &font_path, GLuint height);
};
