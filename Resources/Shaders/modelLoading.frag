#version 330 core

in vec2 TexCoords;
out vec4 colour;
uniform sampler2D texture_diffuse;

void main(void)
{
	colour = vec4(texture(texture_diffuse, TexCoords));
}