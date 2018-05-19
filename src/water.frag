/**
 * @file water.frag
 * @brief Fragment Shader
 * @author Samuel Gauthier
 */
#version 400

// Schlick's R(theta=0) = ((1-1.333)/(1+1.333))^2
#define F0 0.02037318784
// air/water = 1/1.333
#define RATIO 0.7501875469
#define PI 3.14159265358979
#define TCST1 0.1

uniform samplerCube cube_texture;
uniform sampler2D normalMap;
uniform mat4 M, V;
uniform float t;

// Normal attenuation constant
const vec3 normalAttenuation = vec3(0.1, 1, 0.1);

in vec3 l_position;
in vec3 l_normal;
in vec3 l_tangent;
in vec3 l_light_position;
in float roughness;

out vec4 out_Color;

vec3 calculateNormal(vec3 a, float t_cst);
float F(float F_0, vec3 v, vec3 h);
float G_smith(float nx, float k);
float G(float nl, float nv, float k);
float D(float nh, float alpha2);

void main(void) {

    // Compute the needed constants for the specular BRDF
    float alpha = roughness * roughness;
    float alpha2 = alpha * alpha;
    float k = alpha / 2;

    mat4 inverse_V = inverse(V);

    // Transform the position and light position into eye space
    vec3 vm_position = vec3(V * M * vec4(l_position, 1.0));
    vec3 incident_eye = normalize(vm_position);
    vec3 lightPosition = vec3(V * M * vec4(l_light_position, 1.0));

    // Compute the normal, view, light and half vector
    vec3 n = normalize(calculateNormal(normalAttenuation, TCST1));
    vec3 v = normalize(vec3(V[2]) - vm_position);
    vec3 l = normalize(lightPosition - vm_position);
    vec3 h = normalize(l + v);

    // Precompute the dot products for the specular BRDF
    float nl = max(dot(n, l), 0);
    float nv = max(dot(n, v), 0);
    float nh = max(dot(n, h), 0);

    // Reflect ray around normal from eye to surface
    vec3 reflected = reflect(incident_eye, n);
    reflected = vec3(inverse_V * vec4(reflected, 0.0));
    
    // Compute the refraction vector
    vec3 refracted = refract(incident_eye, n, RATIO);
    refracted = vec3(inverse_V * vec4(refracted, 0.0));
    
    // Fetch the corresponding reflection and refraction colors from the cube
    // map
    vec4 reflectionColor = texture(cube_texture, reflected);
    vec4 refractionColor = texture(cube_texture, refracted);
    
    // Compute the ambient color
    vec4 ambient = mix(refractionColor, reflectionColor, F(F0, v, n));

    float F_v = F(F0, l, h);
    float G = G(nl, nv, k);
    float D = D(nh, alpha2);

    // Compute the specular color
    float specular = F_v * G * D / max(4 * nl * nv, 0.001);

    // Set the color of the fragment
    out_Color = specular + ambient;
}

// Convert the normal form the normal map to the eye space. Attenuate it by a
// factor a and attenuate the time scroll with a factor t_cst
vec3 calculateNormal(vec3 a, float t_cst) {

    // Gram-Schmidt process to re-orthogonalize the vectors
    vec3 normal = normalize(l_normal);
    vec3 tangent = normalize(l_tangent);
    tangent = normalize(tangent - dot(tangent, normal) * normal);

    // Fetch the normal from the normal map
    vec3 binormal = cross(tangent, normal);
    vec3 bumpMapNormal = texture(normalMap, l_position.xz + t_cst *
            vec2(t)).xyz;
    bumpMapNormal = 2.0 * bumpMapNormal - vec3(1.0, 1.0, 1.0);

    // Create TBN matrix
    mat3 tbn = mat3(tangent, binormal, normal);

    // Transform the bumped normal int local space, dampen it and transform it
    // into the eye space.
    vec3 newNormal = tbn * bumpMapNormal;
    newNormal = normalize(a * newNormal);
    return vec3(V * M * vec4(newNormal, 0));
}

// Shlick approximation
float F(float F_0, vec3 v, vec3 h) {

    return F_0 + (1 - F_0) * pow((1 - max(dot(v, h), 0)), 5);
}

float G_smith(float nx, float k) {

    return nx / (nx * (1 - k) + k);
}

// Height correlated Smith
float G(float nl, float nv, float k) {

    return G_smith(nl, k) * G_smith(nv, k);
}

// Trowbridge-Reitz
float D(float nh, float alpha2) {

    float denom = nh * nh * (alpha2 - 1) + 1;
    return alpha2 / (PI * denom * denom);
}
