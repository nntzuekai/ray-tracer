#version 300 es

precision mediump float; 

in vec4 vPosition;
in vec2 vTexCoord;

out vec2 texCoord;

void main() 
{
    gl_Position = vPosition;
	texCoord = vTexCoord;
} 
