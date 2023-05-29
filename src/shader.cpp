#include "shader.hpp"
#include "utils.hpp"
#include "logger.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <fstream>

Shader::Shader(const std::string &vertex_path, const std::string &fragment_path)
{
    std::string vertex_src = read_shader_file(vertex_path);
    std::string fragment_src = read_shader_file(fragment_path);

    create_shader(vertex_src, fragment_src);
}

Shader::~Shader()
{
    if (m_program != 0)
        glDeleteProgram(m_program);
}

void Shader::use()
{
    glUseProgram(m_program);
}

void Shader::set_float(const char *name, float value)
{
    glUniform1f(glGetUniformLocation(m_program, name), value);
}

void Shader::set_int(const char *name, int value)
{
    glUniform1i(glGetUniformLocation(m_program, name), value);
}

void Shader::set_vec2(const char *name, const glm::vec2 &vec)
{
    glUniform2f(glGetUniformLocation(m_program, name), vec.x, vec.y);
}

void Shader::set_vec3(const char *name, const glm::vec3 &vec)
{
    glUniform3f(glGetUniformLocation(m_program, name), vec.x, vec.y, vec.z);
}

void Shader::set_vec4(const char *name, const glm::vec4 &vec)
{
    glUniform4f(glGetUniformLocation(m_program, name), vec.x, vec.y, vec.z, vec.w);
}

void Shader::set_mat4(const char *name, const glm::mat4 &mat)
{
    glUniformMatrix4fv(glGetUniformLocation(m_program, name), 1, false, glm::value_ptr(mat));
}

std::string Shader::read_shader_file(const std::string &file_path)
{
    std::ifstream stream(file_path, std::ios::in);
    if (!stream.is_open())
    {
        logger::error("Failed to open file %s.", file_path.c_str());
        return "";
    }

    std::string source;
    size_t size = utils::file_size(file_path);
    source.resize(size);
    stream.read(&source[0], size);

    return source;
}

GLuint Shader::compile(GLuint type, const char *source)
{
    GLuint shader = glCreateShader(type);

    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint result = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        GLint size = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &size);

        std::string info;
        info.resize(size);
        glGetShaderInfoLog(shader, size, &size, &info[0]);
        logger::error("Shader compilation failed, info: %s", info.c_str());
        glDeleteShader(shader);

        return 0;
    }

    return shader;
}

void Shader::create_shader(const std::string &vertex_src, const std::string &fragment_src)
{
    GLuint vertex_shader = compile(GL_VERTEX_SHADER, vertex_src.c_str());
    GLuint fragment_shader = compile(GL_FRAGMENT_SHADER, fragment_src.c_str());

    if (vertex_shader == 0 || fragment_shader == 0)
        return;

    m_program = glCreateProgram();

    glAttachShader(m_program, vertex_shader);
    glAttachShader(m_program, fragment_shader);

    glLinkProgram(m_program);

    GLint result = GL_FALSE;
    glGetProgramiv(m_program, GL_LINK_STATUS, &result);
    if (result == GL_FALSE)
    {
        GLint size = 0;
        glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &size);

        std::string info;
        info.resize(size);
        glGetProgramInfoLog(m_program, size, &size, &info[0]);
        logger::error("Failed to link vertex and fragment shader, info: %s", info.c_str());
        glDeleteProgram(m_program);

        return;
    }

    glValidateProgram(m_program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}
