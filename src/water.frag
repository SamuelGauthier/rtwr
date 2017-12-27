#version 400

// Schlick's R(theta=0) = ((1-1.33)/(1+1.33))^2
#define R_F0 0.0200593122
// water/air = 1/1.333
#define RATIO 0.75

in vec3 vm_position;
in vec3 vm_normal;

in vec3 binormal;
in vec3 tangent;
in vec3 normal;

uniform samplerCube cube_texture;
uniform mat4 M, V;

out vec4 out_Color;

void main(void) {

    vec3 light_position = vec3(9, 9, -3);

    /* reflect ray around normal from eye to surface */
    vec3 incident_eye = normalize(vm_position);
    vec3 normal = normalize(vm_normal);
    //vec3 normal = (vm_normal);

    vec3 view = normalize(vec3(V[1]) - vm_position);
    vec3 l = normalize(light_position - vm_position);
    vec3 h = normalize(l + view);

    //mat3 objectToWorldMatrix = mat3(normalize(binormal), normalize(normal),
    //        normalize(tangent));
    //vec3 worldNormal = objectToWorldMatrix * normal;

    vec3 reflected = reflect(incident_eye, normal);
    //vec3 reflected = reflect(incident_eye, worldNormal);
    // convert from eye to world space
    reflected = vec3(inverse(V) * vec4(reflected, 0.0));

    //float ratio = 1.0 / 1.3333;
    vec3 refracted = refract(incident_eye, normal, RATIO);
    //vec3 refracted = refract(incident_eye, worldNormal, ratio);
    refracted = vec3(inverse(V) * vec4(refracted, 0.0));

    vec4 reflectionColor = texture(cube_texture, reflected);
    vec4 refractionColor = texture(cube_texture, refracted);

    float R_coeff = R_F0 + (1.0 - R_F0) * pow((1.0 - max(0.0, dot(normal,
                        view) / (length(normal) * length(view)))), 5);
    //float R_coeff = R_F0 + (1.0 - R_F0) *
    //    pow((1.0 - max(0.0, dot(worldNormal, vm_position))), 5);
    //vec4 test = vec4(R_coeff, 0, 0, 0);
    //out_Color = test;

    out_Color = mix(refractionColor, reflectionColor, R_coeff);
    //out_Color = vec4(1,0,0,1);
    //out_Color = I_total;
}
