#version 410
layout (location = 0) in vec3 SELF_POSITION;

#pragma CUSTOM_UNIFORMS

// consts
vec4 POSITION;

void main()
{
    #pragma CUSTOM_VERTEX_CODE
    gl_Position = POSITION;
}