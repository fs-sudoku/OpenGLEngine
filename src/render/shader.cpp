#include "shader.h"

#include <render\render.h>
#include <render\shader_processor.h>
#include <render\world_matrix.h>
#include <core\core.h>
#include <utils\file_io.h>

#include <GL\glew.h>
#include <GLM\gtc\type_ptr.hpp>

#define MODEL_LOCATION          0u
#define VIEW_LOCATION           1u
#define PROJECTION_LOCATION     2u
#define TIME_LOCATION           3u

void Shader::check_gl_errors(const uint& id) const
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
    core->shader_proc->shaders.push_back(this);

    auto tuple = core->shader_proc->get_completed_shader(path);
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
    this->base_locations = core->shader_proc->get_base_locations(id);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use() const
{
    glUseProgram(this->id);
}

void Shader::set_bool(const cstr& name, bool value) const
{
    glUniform1i(
        glGetUniformLocation(id, name.c_str()), value
    );
}

void Shader::set_int(const cstr& name, int value) const
{
    glUniform1i(
        glGetUniformLocation(id, name.c_str()), value
    );
}

void Shader::set_uint(const cstr& name, uint value) const
{
    glUniform1ui(
        glGetUniformLocation(id, name.c_str()), value
    );
}

void Shader::set_float(const cstr& name, float value) const
{
    glUniform1f(
        glGetUniformLocation(id, name.c_str()), value
    );
}

void Shader::set_mat4(const cstr& name, const glm::mat4& value) const
{
    glUniformMatrix4fv(glGetUniformLocation(
        id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value)
    );
}

void Shader::auto_set_matrix(uint location, const glm::mat4& mat)
{
    glUniformMatrix4fv(
        location, 1, GL_FALSE, glm::value_ptr(mat)
    );
}

void Shader::auto_set_uint(uint location, uint value)
{
    glUniform1ui(
        location, value
    );
}

void Shader::set_base_uniforms(const WorldMatrix* world_matrix, float ticks)
{
    auto_set_matrix(base_locations[MODEL_LOCATION],         world_matrix->model);
    auto_set_matrix(base_locations[VIEW_LOCATION],          world_matrix->view);
    auto_set_matrix(base_locations[PROJECTION_LOCATION],    world_matrix->projection);

    auto_set_uint(base_locations[TIME_LOCATION],            ticks);
}
