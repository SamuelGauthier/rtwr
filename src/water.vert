#version 400

#define PI 3.14159265358979
#define NUMWAVES 3
#define Q 0.2
//#define Q 0.9


layout(location=0) in vec4 in_Position;
layout(location=1) in vec4 in_Color;
layout(location=2) in vec3 in_Normal;

uniform mat4 M, V, P;
uniform float t;

out vec3 pos_eye;
out vec3 n_eye;

out vec3 binormal;
out vec3 tangent;
out vec3 normal;

void main(void) {
    
    //float t = 0.0;

    float w[3] = float[](sqrt(9.81 * (2 * PI) / 1.0), sqrt(9.81 * (4 * PI)),
                sqrt(9.81 * (10 * PI)));
    float phi[3] = float[](0.4 * w[0], 0.3 * w[1], 0.3 * w[2]);
    //float A[3] = float[](0.06, 0.02, 0.007);
    float A[3] = float[](0.02, 0.01, 0.037);
    float Qs[3] = float[](Q/(w[0] * A[0] * NUMWAVES), Q/(w[1] * A[1] *
                NUMWAVES), Q/(w[2] * A[2] * NUMWAVES));
    //vec2 D[3] = vec2[](vec2(0.24, 0.34), vec2(0.75, 0.14), vec2(0.45, 0.24));
    vec2 D[3] = vec2[](vec2(0.0, 0.5), vec2(0.8, 0.7), vec2(0.6, 0.6));
    vec4 position = in_Position;
    //vec3 binormal = vec3(1.0, 0.0, 0.0);
    //vec3 tangent = vec3(0.0, 1.0, 0.0);
    //vec3 normal = vec3(0.0, 0.0, 1.0);
    binormal = vec3(1.0, 0.0, 0.0);
    tangent = vec3(0.0, 1.0, 0.0);
    normal = vec3(0.0, 0.0, 1.0);

    for(int i = 0; i < NUMWAVES; i++) {
        float alpha = w[i] * dot(D[i], position.xz) + phi[i] * t;
        //float phase = phi[i] * t;
        float WA = w[i] * A[i];

        position.x += Qs[i] * A[i] * D[i].x * cos(alpha);
        position.z += Qs[i] * A[i] * D[i].y * cos(alpha);
        position.y += A[i] * sin(alpha);

        binormal.x -= Qs[i] * D[i].x * D[i].x * WA * sin(alpha);
        binormal.y -= Qs[i] * D[i].x * D[i].y * WA * sin(alpha);
        binormal.z += D[i].x * WA * cos(alpha);

        tangent.x -= Qs[i] * D[i].x * D[i].y * WA * sin(alpha);
        tangent.y -= Qs[i] * D[i].y * D[i].y * WA * sin(alpha);
        tangent.z += D[i].y * WA * cos(alpha);

        //normal.x -= D[i].x * WA * cos(alpha);
        //normal.y -= D[i].y * WA * cos(alpha);
        //normal.x -= Qs[i] * WA * sin(alpha);
    }

    //normal = -normal;
    normal = cross(tangent, binormal);

    //normal = normalize(position.xyz);
    pos_eye = vec3(V * M * position);
    n_eye = vec3(V * M * vec4(normal, 0.0));
    gl_Position = P * V * M * position;
}
