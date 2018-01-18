/**
 * @file water.vert
 * @brief Vertex Shader
 * @author Samuel Gauthier
 */
#version 400

// Define constants
#define PI 3.14159265358979
#define NUMWAVES 4
#define Q 0.2

layout(location=0) in vec4 in_Position;

uniform sampler2D normalMap;
uniform mat4 M, V, P;
uniform float t;

out vec3 l_position;
out vec3 l_normal;
out vec3 l_tangent;
out vec3 l_light_position;
out float roughness;

void main(void) {

    // Definition of the angular frequencies, phases, amplitudes, directions. 
    float w[4] = float[](
            sqrt(9.81 * 2 * PI), sqrt(9.81 * 4 * PI),
            sqrt(9.81 * 10 * PI), sqrt(9.81 * PI));
    float phi[4] = float[](0.4 * w[0], 0.3 * w[1], 0.3 * w[2], 0.1 * w[3]);
    float A[4] = float[](0.01, 0.008, 0.017, 0.003);
    float Qs[4] = float[](
            Q/(w[0] * A[0] * NUMWAVES), Q/(w[1] * A[1] * NUMWAVES),
            Q/(w[2] * A[2] * NUMWAVES), Q/(w[3] * A[3] * NUMWAVES));
    vec2 D[4] = vec2[](vec2(0.0, 0.5), vec2(0.8, 0.7), vec2(0.6, 0.6),
            vec2(0.7, -0.3));

    vec4 position = in_Position;
    vec3 normal = vec3(0.0, 1.0, 0.0);
    vec3 tangent = vec3(0.0, 0.0, 1.0);

    // y and z coordinates are flipped in OpenGL
    // z coordinate points out of the screen.
    for(int i = 0; i < NUMWAVES; i++) {
        float alpha = w[i] * dot(D[i], position.xz) + phi[i] * t;
        float WA = w[i] * A[i];
        float sinAlpha = sin(alpha);
        float cosAlpha = cos(alpha);
        float DxCos = D[i].x * cosAlpha;
        float DyCos = D[i].y * cosAlpha;
        float DxDy = D[i].x * D[i].y;

        // Compute the postion, normal and tangent vectors.
        position.x += Qs[i] * A[i] * DxCos;
        position.y += A[i] * sinAlpha;
        position.z += Qs[i] * A[i] * DyCos;

        normal.x -= D[i].x * WA * cosAlpha;
        normal.y -= Qs[i] * WA * sinAlpha;
        normal.z -= D[i].y * WA * cosAlpha;

        tangent.x -= Qs[i] * DxDy * WA * sinAlpha;
        tangent.y += D[i].y * WA * cosAlpha;
        tangent.z -= Qs[i] * D[i].y * D[i].y * WA * sinAlpha;
    }

    // Pass the postion, normal, tangent and light postion in local space to the
    // fragment shader
    l_position = vec3(position);
    l_normal = normalize(normal);
    l_tangent = normalize(tangent);

    l_light_position = vec3(-9, 9, -9);
    roughness = 0.1;

    // Set the postion of the vertex
    gl_Position = P * V * M * position;
}
