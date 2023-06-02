#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <cstdint>
#include <string>

class Texture
{
public:
    Texture() = default;
    ~Texture() = default;

    const GLuint get_id() const;
    void bind() const;

    bool load(const std::string &image_path);
    void delete_texture();

private:
    GLuint m_id = 0;
    GLuint m_width = 0;
    GLuint m_height = 0;
    GLuint m_channels = 0;
    GLuint m_internal_format = GL_RGBA;
    GLuint m_image_format = GL_RGBA;
};
