#pragma once
#include <base_types\base_types.h>
#include <utils\utils.h>

#include <GLM\matrix.hpp>

class Shader
{
public:
    Shader(const cstr& path);
    void use() const;
    void set_bool(const cstr& name, bool value) const;
    void set_int(const cstr& name, int value) const;
    void set_uint(const cstr& name, uint value) const;
    void set_float(const cstr& name, float value) const;
    void set_mat4(const cstr& name, const glm::mat4& value) const;
public:
    void set_base_uniforms(const struct WorldMatrix* world_matrix, float ticks);
private:
    void check_gl_errors(const uint& id) const;
    void auto_set_matrix(uint location, const glm::mat4& mat);
    void auto_set_uint(uint location, uint value);
private:
    std::vector<uint> base_locations;
    uint id = 0u;
};