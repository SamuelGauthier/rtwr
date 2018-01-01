#version 400

// Schlick's R(theta=0) = ((1-1.33)/(1+1.33))^2
#define R_F0 0.0200593122
// water/air = 1/1.333
#define RATIO 0.75

in vec3 vm_position;
in vec3 vm_normal;

//in vec3 binormal;
//in vec3 tangent;
//in vec3 normal;

uniform samplerCube cube_texture;
uniform mat4 M, V;

out vec4 out_Color;

// Shlick approximation, use v instead of l?
float F(float F_0, vec3 l, vec3 h) {

    return F_0 + (1 - F_0) * pow((1 - max(0, dot(l, h))), 5);
}

void main(void) {

    vec3 light_position = vec3(9, 9, -9);
    vec3 E_L = vec3(0.7, 0.7, 0.7);
    mat4 inverse_V = inverse(V);

    /* reflect ray around normal from eye to surface */
    vec3 incident_eye = normalize(vm_position);
    vec3 n = normalize(vm_normal);
    vec3 v = normalize(vec3(V[1]) - vm_position);
    vec3 l = normalize(light_position - vm_position);
    vec3 h = normalize(l + v);

    vec3 reflected = reflect(incident_eye, n);
    //vec3 reflected = reflect(incident_eye, worldNormal);
    // convert from eye to world space
    reflected = vec3(inverse_V * vec4(reflected, 0.0));

    //float ratio = 1.0 / 1.3333;
    vec3 refracted = refract(incident_eye, n, RATIO);
    //vec3 refracted = refract(incident_eye, worldNormal, ratio);
    refracted = vec3(inverse_V * vec4(refracted, 0.0));

    vec4 reflectionColor = texture(cube_texture, reflected);
    vec4 refractionColor = texture(cube_texture, refracted);

    float R_coeff = R_F0 + (1.0 - R_F0) * pow((1.0 - max(0.0, dot(n,
                        v) / (length(n) * length(v)))), 5);
    //float R_coeff = R_F0 + (1.0 - R_F0) *
    //    pow((1.0 - max(0.0, dot(worldNormal, vm_position))), 5);
    //vec4 test = vec4(R_coeff, 0, 0, 0);
    //out_Color = test;

    out_Color = mix(refractionColor, reflectionColor, R_coeff);
    //out_Color = vec4(1,0,0,1);
    //out_Color = I_total;
}
