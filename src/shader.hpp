#pragma once

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader
{
public:
    Shader() = default;
    ~Shader() = default;

    bool load(const std::string &vertex_path, const std::string &fragment_path);
    void use();
    void delete_program();

    void set_float(const char *name, float value);
    void set_int(const char *name, int value);
    void set_vec2(const char *name, const glm::vec2 &vec);
    void set_vec3(const char *name, const glm::vec3 &vec);
    void set_vec4(const char *name, const glm::vec4 &vec);
    void set_mat4(const char *name, const glm::mat4 &mat);

private:
    GLuint m_program_id = 0;

    std::string read_shader_file(const std::string &file_path);
    GLuint compile(GLuint type, const char *source);
    bool create_program(const std::string &vertex_src, const std::string &fragment_src);
};
