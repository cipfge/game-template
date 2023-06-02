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
    int nr_channels = 0;

    uint8_t *data = stbi_load(image_path.c_str(), &width, &height, &nr_channels, 0);
    if (!data)
    {
        logger::error("Cannot load image %s.", image_path.c_str());
        return false;
    }

    generate(width, height, data);

    stbi_image_free(data);
    return true;
}

void Texture::delete_texture()
{
    glDeleteTextures(1, &m_id);
}

void Texture::generate(GLuint width, GLuint height, uint8_t *data)
{
    m_width = width;
    m_height = height;

    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexImage2D(GL_TEXTURE_2D, 0, m_internal_format, width, height, 0, m_image_format, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrap_t);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filter_min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filter_max);

    glBindTexture(GL_TEXTURE_2D, 0);
}
