#pragma once
#include <base_types\base_types.h>

#include <GLM\matrix.hpp>

class Shader
{
public:
    Shader(const cstr& path);
    void use();
    void set_bool(const cstr& name, bool value);
    void set_int(const cstr& name, int value);
    void set_float(const cstr& name, float value);
    void set_mat4(const cstr& name, const glm::mat4& value);
private:
    void check_gl_errors(const uint& id);
    uint id = 0;
};