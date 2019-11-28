#version 300 es

precision mediump float; 

in vec2 texCoord;

out vec4  fColor;

uniform sampler2D texture;

void main() 
{ 
	fColor = texture2D( texture, texCoord );
} 

