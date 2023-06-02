#pragma once

#include "shader.hpp"
#include "texture.hpp"
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
    Renderer() = default;
    ~Renderer() = default;

    bool init(int width, int height);
    void cleanup();
    void resize(int width, int height);
    void render_text(const std::string &text, float x, float y, float scale, glm::vec3 color);
    void render_sprite(const Texture &texture, glm::vec2 position, glm::vec2 size, glm::vec3 color, float rotation);

private:
    Shader m_text_shader;
    Shader m_sprite_shader;
    std::map<char, Character> m_characters;
    int m_width = 0;
    int m_height = 0;
    GLuint m_text_vao;
    GLuint m_text_vbo;
    GLuint m_sprite_vao;
    GLuint m_sprite_vbo;

    bool load_font(const std::string &font_path, GLuint height);
};
