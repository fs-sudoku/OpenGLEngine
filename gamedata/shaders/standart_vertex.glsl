#version 410
layout (location = 0) in vec3 SELF_POSITION;
layout (location = 1) in vec3 NORMAL;

#pragma CUSTOM_UNIFORMS

uniform mat4 MODEL;
uniform mat4 VIEW;
uniform mat4 PROJECTION;

uniform int TIME;

void main()
{
    #pragma CUSTOM_VERTEX_CODE
}