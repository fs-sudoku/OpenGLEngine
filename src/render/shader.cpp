#include "shader.h"

#include <core\core.h>
#include <utils\file_io.h>
#include <GL\glew.h>

Shader::Shader(const cstr vertex_path, const cstr fragment_path)
{
    const char* v_shader_ptr = utils::io::read_file(vertex_path).c_str();
    const char* f_shader_ptr = utils::io::read_file(fragment_path).c_str();

    unsigned int vertex, fragment;
    int success;
    char info_log[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &v_shader_ptr, NULL);
    glCompileShader(vertex);

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &f_shader_ptr, NULL);
    glCompileShader(fragment);

    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, info_log);
        core->fatal_error(utils::format("Cannot compile shader! Log: %s", info_log));
    };

    id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);

    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(id, 512, NULL, info_log);
        core->fatal_error(utils::format("Cannot compile shader! Log: %s", info_log));
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use()
{
    glUseProgram(this->id);
}

void Shader::set_bool(const cstr name, bool value) const
{

}

void Shader::set_int(const cstr name, int value) const
{

}

void Shader::set_float(const cstr name, float value) const
{

}