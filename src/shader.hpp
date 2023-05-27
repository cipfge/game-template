#pragma once

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader
{
public:
    Shader(const std::string &vertex_path, const std::string &fragment_path);
    ~Shader();

    void use();

private:
    GLuint m_program = 0;

    std::string read_shader_file(const std::string &file_path);
    GLuint compile(GLuint type, const char *source);
    void create_shader(const std::string &vertex_src, const std::string &fragment_src);
};
