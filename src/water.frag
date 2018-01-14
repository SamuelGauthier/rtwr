#version 400

// Schlick's R(theta=0) = ((1-1.33)/(1+1.33))^2
#define R_F0 0.0200593122
// water/air = 1/1.333
#define RATIO 0.75
#define PI 3.14159265358979
#define TCST1 0.1

const vec3 normalAttenuation = vec3(0.1, 1, 0.1);

in vec3 vm_position;
in vec3 vm_normal;
in vec3 light_position;
in vec3 E_L;
in float roughness;
in vec3 m_position;
in vec3 m_normal;
in vec3 m_tangent;

uniform samplerCube cube_texture;
uniform mat4 M, V;
uniform sampler2D normalMap;
uniform float t;

out vec4 out_Color;

vec3 calculateNormal(vec3 a, float t_cst);
float F(float F_0, vec3 v, vec3 h);
float G_smith(float nx, float k);
float G(float nl, float nv, float k);
float D(float nh, float alpha2);

void main(void) {

    float alpha = roughness * roughness;
    float alpha2 = alpha * alpha;
    float k = alpha / 2;
    mat4 inverse_V = inverse(V);

    vec3 incident_eye = normalize(vm_position);
    vec3 lightPosition = vec3(V * M * vec4(light_position, 1.0));
    vec3 n = normalize(calculateNormal(normalAttenuation, TCST1));
    //vec3 n = normalize(vm_normal);
    vec3 v = normalize(vec3(V[2]) - vm_position);
    vec3 l = normalize(lightPosition - vm_position);
    vec3 h = normalize(l + v);
    float nl = max(dot(n, l), 0);
    float cnl = max(0, nl);
    float nv = max(dot(n, v), 0);
    float nh = max(dot(n, h), 0);

    /* reflect ray around normal from eye to surface */
    vec3 reflected = reflect(incident_eye, n);
    reflected = vec3(inverse_V * vec4(reflected, 0.0));
    
    vec3 refracted = refract(incident_eye, n, RATIO);
    refracted = vec3(inverse_V * vec4(refracted, 0.0));
    
    vec4 reflectionColor = texture(cube_texture, reflected);
    vec4 refractionColor = texture(cube_texture, refracted);
    
    vec4 ambient = mix(refractionColor, reflectionColor, F(R_F0, v, n));

    float F = F(R_F0, l, h);
    float G = G(nl, nv, k);
    float D = D(nh, alpha2);

    float specular = F * G * D / max(4 * nl * nv, 0.001);

    out_Color = specular + ambient + cnl * vec4(E_L, 1);
}

// Convert the normal form the normal map to the eye space. Attenuate it by a
// factor a and Attenuate the time scroll with a factor t_cst
vec3 calculateNormal(vec3 a, float t_cst) {

    vec3 normal = normalize(m_normal);
    vec3 tangent = normalize(m_tangent);
    tangent = normalize(tangent - dot(tangent, normal) * normal);
    vec3 bitangent = cross(tangent, normal);
    vec3 bumpMapNormal = texture(normalMap, m_position.xz + t_cst *
            vec2(t)).xyz;

    bumpMapNormal = 2.0 * bumpMapNormal - vec3(1.0, 1.0, 1.0);
    mat3 tbn = mat3(tangent, bitangent, normal);
    vec3 newNormal = tbn * bumpMapNormal;
    newNormal = normalize(a * newNormal);
    return vec3(V * M * vec4(newNormal, 0));
}

// Shlick approximation, use l or v?
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
