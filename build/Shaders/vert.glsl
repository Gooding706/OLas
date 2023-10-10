#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aColor; // the color variable has attribute position 1
  
out vec2 UV; // output a color to the fragment shader
uniform float UTime;

void main()
{
    gl_Position = vec4(aPos.x+sin(UTime*0.5f), aPos.y+sin(UTime*2.0f), aPos.z, 1.0);
    UV = aColor;
}