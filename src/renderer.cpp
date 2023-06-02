#include "renderer.hpp"
#include "logger.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

bool Renderer::init(int width, int height)
{
    m_width = width;
    m_height = height;

    // Text render data
    if (!m_text_shader.load("text.vs", "text.fs"))
        return false;

    m_text_shader.use();
    m_text_shader.set_int("text", 0);

    if (!load_font("game_font.ttf", 48))
        return false;

    glGenVertexArrays(1, &m_text_vao);
    glGenBuffers(1, &m_text_vbo);
    glBindVertexArray(m_text_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_text_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Sprite render data
    if (!m_sprite_shader.load("sprite.vs", "sprite.fs"))
        return false;

    m_sprite_shader.use();
    m_sprite_shader.set_int("sprite", 0);

    float vertices[] = {
       0.0f, 1.0f, 0.0f, 1.0f,
       1.0f, 0.0f, 1.0f, 0.0f,
       0.0f, 0.0f, 0.0f, 0.0f,

       0.0f, 1.0f, 0.0f, 1.0f,
       1.0f, 1.0f, 1.0f, 1.0f,
       1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &m_sprite_vao);
    glGenBuffers(1, &m_sprite_vbo);

    glBindBuffer(GL_ARRAY_BUFFER, m_sprite_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(m_sprite_vao);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return true;
}

void Renderer::cleanup()
{
    for (auto it: m_characters)
        glDeleteTextures(1, &it.second.texture_id);
    m_characters.clear();

    m_text_shader.delete_program();
    m_sprite_shader.delete_program();

    glDeleteVertexArrays(1, &m_sprite_vao);
    glDeleteVertexArrays(1, &m_text_vao);
}

void Renderer::resize(int width, int height)
{
    m_width = width;
    m_height = height;
}

void Renderer::render_text(const std::string &text, float x, float y, float scale, glm::vec3 color)
{
    m_text_shader.use();
    m_text_shader.set_mat4("projection", glm::ortho(0.0f, static_cast<float>(m_width), static_cast<float>(m_height), 0.0f));
    m_text_shader.set_vec3("text_color", color);

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(m_text_vao);

    for (std::string::const_iterator c = text.begin(); c != text.end(); c++)
    {
        Character ch = m_characters[*c];

        float xpos = x + ch.bearing.x * scale;
        float ypos = y + (m_characters['H'].bearing.y - ch.bearing.y) * scale;
        float w = ch.size.x * scale;
        float h = ch.size.y * scale;

        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 0.0f },
            { xpos,     ypos,       0.0f, 0.0f },

            { xpos,     ypos + h,   0.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 0.0f }
        };

        glBindTexture(GL_TEXTURE_2D, ch.texture_id);
        glBindBuffer(GL_ARRAY_BUFFER, m_text_vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        x += (ch.advance >> 6) * scale;
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::render_sprite(const Texture &texture, glm::vec2 position, glm::vec2 size, glm::vec3 color, float rotation)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f));

    m_sprite_shader.use();
    m_sprite_shader.set_mat4("projection", glm::ortho(0.0f, static_cast<float>(m_width), static_cast<float>(m_height), 0.0f));
    m_sprite_shader.set_mat4("model", model);
    m_sprite_shader.set_vec3("sprite_color", color);

    glActiveTexture(GL_TEXTURE0);
    texture.bind();

    glBindVertexArray(m_sprite_vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

bool Renderer::load_font(const std::string &font_path, GLuint height)
{
    m_characters.clear();

    FT_Library font_library;
    if (FT_Init_FreeType(&font_library))
    {
        logger::error("Cannot initialize FreeType.");
        return false;
    }

    FT_Face font_face;
    if (FT_New_Face(font_library, font_path.c_str(), 0, &font_face))
    {
        logger::error("Cannot load font %s.", font_path.c_str());
        return false;
    }

    FT_Set_Pixel_Sizes(font_face, 0, height);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Create font texture cache
    for (unsigned char c = 0; c < 128; c++)
    {
        if (FT_Load_Char(font_face, c, FT_LOAD_RENDER))
        {
            logger::warning("Failed to load glyph %u", c);
            continue;
        }

        GLuint texture_id = 0;
        glGenTextures(1, &texture_id);
        glBindTexture(GL_TEXTURE_2D, texture_id);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, font_face->glyph->bitmap.width,
                     font_face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE,
                     font_face->glyph->bitmap.buffer);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character chr;
        chr.texture_id = texture_id;
        chr.size = glm::ivec2(font_face->glyph->bitmap.width, font_face->glyph->bitmap.rows);
        chr.bearing = glm::ivec2(font_face->glyph->bitmap_left, font_face->glyph->bitmap_top);
        chr.advance = static_cast<unsigned int>(font_face->glyph->advance.x);

        m_characters[c] = chr;
    }

    glBindTexture(GL_TEXTURE_2D, 0);

    FT_Done_Face(font_face);
    FT_Done_FreeType(font_library);

    return true;
}
