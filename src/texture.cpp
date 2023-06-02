#include "texture.hpp"
#include "stb_image.h"
#include "logger.hpp"

const GLuint Texture::get_id() const
{
    return m_id;
}

void Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, m_id);
}

bool Texture::load(const std::string &image_path)
{
    int width = 0;
    int height = 0;
    int channels = 0;

    uint8_t *data = stbi_load(image_path.c_str(), &width, &height, &channels, 0);
    if (!data)
    {
        logger::error("Cannot load image %s.", image_path.c_str());
        return false;
    }

    m_width = width;
    m_height = height;
    m_channels = channels;

    switch (m_channels)
    {
    case 4:
        m_internal_format = GL_RGBA8;
        m_image_format = GL_RGBA;
        break;

    case 3:
        m_internal_format = GL_RGB8;
        m_image_format = GL_RGB;
        break;

    default:
        m_internal_format = GL_RGBA;
        m_image_format = GL_RGBA;
        break;
    }

    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, m_internal_format, width, height, 0, m_image_format, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(data);

    return true;
}

void Texture::delete_texture()
{
    glDeleteTextures(1, &m_id);
}
