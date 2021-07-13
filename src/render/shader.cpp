#include "shader.h"

#include <core\core.h>
#include <utils\file_io.h>
#include <GL\glew.h>

void Shader::check_gl_errors(const uint& id)
{
    int success;
    char info_log[512];

    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(id, 512, NULL, info_log);
        core->fatal_error(utils::format("Cannot compile shader! Log:\n %s", info_log));
    };
}

Shader::Shader(const cstr& vertex_path, const cstr& fragment_path)
{
    cstr v_shader_ptr = utils::io::read_file(vertex_path);
    cstr f_shader_ptr = utils::io::read_file(fragment_path);

    const char* vShaderCode = v_shader_ptr.c_str();
    const char* fShaderCode = f_shader_ptr.c_str();

    uint vertex, fragment;
    int success;
    char info_log[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    this->check_gl_errors(vertex);

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    this->check_gl_errors(fragment);

    id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);
    this->check_gl_errors(id);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use()
{
    glUseProgram(this->id);
}

void Shader::set_bool(const cstr name, bool value)
{
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::set_int(const cstr name, int value)
{
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::set_float(const cstr name, float value)
{
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}