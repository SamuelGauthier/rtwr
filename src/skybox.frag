#version 400

in vec3 texcoords;
uniform samplerCube cube_texture;
out vec4 out_Color;

void main () {
	out_Color = texture (cube_texture, texcoords);
}
