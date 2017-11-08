#version 400

layout(location=0) in vec4 in_Position;
//layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location=1) in vec4 in_Color;
out vec4 ex_Color;

void main(void) {
    //gl_Position.xyz = vertexPosition_modelspace;
    //gl_Position.w = 1.0;
    
    gl_Position = in_Position;
    ex_Color = in_Color;
}
