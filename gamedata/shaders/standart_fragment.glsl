#version 410
out vec4 FragColor;

uniform int TIME;

#pragma CUSTOM_FRAGMENT_VARS

// consts
vec4 COLOR;

void main()
{
    #pragma CUSTOM_FRAGMENT_CODE
    FragColor = COLOR;
}