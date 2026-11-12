#version 330 core

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec3 aColor;

uniform mat4 model;        

layout (std140) uniform Camera
{
    mat4 projection;
    mat4 view;
};

out VS_OUT {
   vec3 color; 
} vs_out;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 0.0, 1.0);
    vs_out.color = aColor;
}