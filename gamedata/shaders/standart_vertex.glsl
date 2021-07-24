#version 410
layout (location = 0) in vec3 Pos;
layout (location = 1) in vec3 Normal;

#pragma CUSTOM_UNIFORMS

uniform vec3 CamPos;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main()
{
    #pragma CUSTOM_VERTEX_CODE
}