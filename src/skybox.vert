#version 400

in vec3 in_Position;
uniform mat4 P, V;
out vec3 texcoords;

void main () {
	texcoords = in_Position;
	gl_Position = P * V * vec4 (in_Position, 1.0);
}
