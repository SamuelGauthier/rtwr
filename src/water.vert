#version 400

layout(location=0) in vec4 in_Position;
layout(location=1) in vec4 in_Color;
layout(location=2) in vec3 in_Normal;

uniform mat4 M, V, P;
uniform float t;


out vec3 pos_eye;
out vec3 n_eye;

void main(void) {

    vec4 position = in_Position;
    position.y = (sin(16.0f*position.x) + cos(16.0f*position.z))/20.0;
    position.y *= sin(float(t));

    pos_eye = vec3(V * M * position);
    n_eye = vec3(V * M * vec4(in_Normal, 0.0));
    gl_Position = P * V * M * position;
}
