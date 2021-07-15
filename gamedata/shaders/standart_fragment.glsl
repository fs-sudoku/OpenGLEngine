#version 410
out vec4 FragColor;

// consts
vec4 COLOR;

void main()
{
    #pragma CUSTOM_FRAGMENT_CODE
    FragColor = COLOR;
}