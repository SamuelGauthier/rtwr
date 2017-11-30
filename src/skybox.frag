#version 400

in vec3 texcoords;
uniform samplerCube cube_texture;
out vec4 out_Color;

void main () {
	out_Color = texture (cube_texture, texcoords);
    //out_Color = vec4(0.0f, 1.0f, 0.0f, 1.0f);
}
