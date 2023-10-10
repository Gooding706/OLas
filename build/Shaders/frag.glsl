#version 330 core
out vec4 FragColor;
in vec2 UV;
uniform sampler2D ourTexture;

uniform float UTime;

void main()
{
    FragColor = texture(ourTexture, UV) * (abs(sin(vec4(UV, 1, 1)+UTime * 3.0f)));
} 