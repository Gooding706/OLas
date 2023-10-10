#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aColor; // the color variable has attribute position 1
  
out vec2 UV; // output a color to the fragment shader
uniform float UTime;
uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;

void main()
{
    gl_Position = projection * view * transform * vec4(aPos, 1.0);
    UV = aColor;
}