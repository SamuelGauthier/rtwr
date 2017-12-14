#version 400

#define R_F0 0.0200593122

in vec3 pos_eye;
in vec3 n_eye;

in vec3 binormal;
in vec3 tangent;
in vec3 normal;

uniform samplerCube cube_texture;
uniform mat4 M, V;

out vec4 out_Color;

void main(void) {

    /* reflect ray around normal from eye to surface */
    vec3 incident_eye = normalize(pos_eye);
    //vec3 normal = normalize(n_eye);
    vec3 normal =(n_eye);

    //mat3 objectToWorldMatrix = mat3(normalize(binormal), normalize(normal),
    //        normalize(tangent));
    //vec3 worldNormal = objectToWorldMatrix * normal;

    vec3 reflected = reflect(incident_eye, normal);
    //vec3 reflected = reflect(incident_eye, worldNormal);
    // convert from eye to world space
    reflected = vec3(inverse(V) * vec4(reflected, 0.0));

    float ratio = 1.0 / 1.3333;
    vec3 refracted = refract(incident_eye, normal, ratio);
    //vec3 refracted = refract(incident_eye, worldNormal, ratio);
    refracted = vec3(inverse(V) * vec4(refracted, 0.0));

    vec4 refractionColor = texture(cube_texture, refracted);
    vec4 reflectionColor = texture(cube_texture, reflected);

    float R_coeff = R_F0 + (1.0 - R_F0) *
        pow((1.0 - max(0.0, dot(normal, pos_eye))), 5);
    //float R_coeff = R_F0 + (1.0 - R_F0) *
    //    pow((1.0 - max(0.0, dot(worldNormal, pos_eye))), 5);

    out_Color = mix(refractionColor, reflectionColor, R_coeff);
    //out_Color = vec4(1,0,0,1);
    //out_Color = I_total;
}
