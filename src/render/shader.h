#pragma once
#include <base_types\base_types.h>

class Shader
{
public:
    Shader(const cstr vertex_path, const cstr fragment_path);
    void use();
    void set_bool(const cstr name, bool value) const;
    void set_int(const cstr name, int value) const;
    void set_float(const cstr name, float value) const;
private:
    uint id = 0;
};