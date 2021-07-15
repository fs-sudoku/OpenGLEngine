#include "shader.h"

#include <render\render.h>
#include <render\shader_processor.h>
#include <core\core.h>
#include <utils\file_io.h>

#include <GL\glew.h>
#include <GLM\gtc\type_ptr.hpp>

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

Shader::Shader(const cstr& path)
{
    core->render->shader_proc->shaders.push_back(this);

    auto tuple = core->render->shader_proc->get_completed_shader(path);
    cstr v_shader_ptr = std::get<0u>(tuple);
    cstr f_shader_ptr = std::get<1u>(tuple);

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

void Shader::set_bool(const cstr& name, bool value)
{
    glUniform1i(
        glGetUniformLocation(id, name.c_str()), value
    );
}

void Shader::set_int(const cstr& name, int value)
{
    glUniform1i(
        glGetUniformLocation(id, name.c_str()), value
    );
}

void Shader::set_float(const cstr& name, float value)
{
    glUniform1f(
        glGetUniformLocation(id, name.c_str()), value
    );
}

void Shader::set_mat4(const cstr& name, const glm::mat4& value)
{
    glUniformMatrix4fv(glGetUniformLocation(
        id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value)
    );
}