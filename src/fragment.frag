#version 400

in vec4 ex_Color;
out vec4 out_Color;

void main(void) {
    out_Color = ex_Color;
    //out_Color = vec3(1,0,0);
}
