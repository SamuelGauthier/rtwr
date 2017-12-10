#version 400
#define PI 3.14159265358979

// define struct for light properties (constants)
struct LightProperties
{
	vec4 position;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};


// define struct for material properties (constants)
struct MaterialProperties
{
	vec4 ambient;		// what part of ambient light is reflected
	vec4 diffuse;		// what part of diffuse light is scattered
	vec4 specular;		// what part of specular light is scattered
	float shininess;	// exponent for sharpening specular reflection
};

LightProperties lightSource = LightProperties(
        vec4(7.0, 9.0, 2.0, 1.0),
        vec4(0.8, 0.8, 0.8, 1.0),
        vec4(0.8, 0.8, 0.8, 1.0),
        vec4(1.0, 1.0, 1.0, 1.0));

MaterialProperties materialProperty = MaterialProperties(
        vec4(0.1, 0.1, 0.1, 1.0),
        vec4(0.1, 0.1, 0.1, 1.0),
        vec4(1.0, 1.0, 1.0, 1.0),
        64.0);

layout(location=0) in vec4 in_Position;
layout(location=1) in vec4 in_Color;
layout(location=2) in vec3 in_Normal;

uniform mat4 M, V, P;
uniform float t;

out vec3 pos_eye;
out vec3 n_eye;
out vec3 normal;
out vec3 position;

out LightProperties light;
out MaterialProperties material;

void main(void) {

    light = lightSource;
    material = materialProperty;
    normal = in_Normal;
    position = in_Position.xyz;

    //float w_i = (2 * PI) / 320.0;
    float w_i = sqrt(9.81 * (2 * PI) / 1.0);
    float phi_i =  0.4 * w_i;
    float A_i = 0.06;
    float Q = 0.9;
    float numWaves = 4;
    float Q_i = Q / (w_i * A_i * numWaves);
    
    vec2 D_i = vec2(0.24, 0.34);
    vec4 position = in_Position;    

    position.x += Q_i * A_i * D_i.x * cos(w_i * dot(D_i, in_Position.xz) +
            phi_i * t);
    position.z += Q_i * A_i * D_i.y * cos(w_i * dot(D_i, in_Position.xz) +
            phi_i * t);
    position.y = A_i * sin(w_i * dot(D_i, in_Position.xz) + phi_i * t);
    w_i = sqrt(9.81 * (4 * PI));
    phi_i =  0.3 * w_i;
    D_i = vec2(0.75, 0.14);
    position.x += Q_i * A_i * D_i.x * cos(w_i * dot(D_i, in_Position.xz) +
            phi_i * t);
    position.z += Q_i * A_i * D_i.y * cos(w_i * dot(D_i, in_Position.xz) +
            phi_i * t);
    position.y += A_i * sin(w_i * dot(D_i, in_Position.xz) + phi_i * t);
    w_i = sqrt(9.81 * (10 * PI));
    phi_i =  0.3 * w_i;
    D_i = vec2(0.45, 0.24);
    position.y += A_i * sin(w_i * dot(D_i, in_Position.xz) + phi_i * t);
    //position.y = A_i * sin(w_i * dot(D_i, in_Position.xz) + phi_i * t);

    //position.y = 0.05 * sin(12 * dot(D_i, position) + t);
    //d_i = vec4(-0.57, 0.23, 0.41, 1.0);
    //position.y += 0.03 * sin(0.6 * (dot(d_i, position) * 22 + t * 2* PI)) / t;
    //d_i = vec4(-0.21, -0.8, -0.21, 1.0);
    //position.y += 0.02 * sin(0.2 * (dot(d_i, position) * 56 + t * 2.5 * PI));
    //d_i = vec4(0.77, -0.63, -0.89, 1.0);
    //position.y += 0.01 * sin(0.5 * (dot(d_i, position) * 72 + t * 2.9 * PI));

    pos_eye = vec3(V * M * position);
    n_eye = vec3(V * M * vec4(in_Normal, 0.0));
    gl_Position = P * V * M * position;
}
