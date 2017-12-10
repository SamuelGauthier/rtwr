#version 400

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

in vec3 pos_eye;
in vec3 n_eye;

uniform samplerCube cube_texture;
uniform mat4 M, V;

in LightProperties light;
in MaterialProperties material;
in vec3 normal;
in vec3 position;

out vec4 out_Color;

void main(void) {

    vec3 ec_position = mat3(M*V) * position;
	mat3 normal_matrix = transpose(inverse( mat3(M*V)));
	vec3 N = normalize(normal_matrix * normal);
	vec3 L = normalize(light.position.xyz - ec_position);
	vec3 V_vec = normalize(ec_position);
	vec3 R = normalize(reflect(-L, N));

    vec4 I_ambient = light.ambient * material.ambient;
    vec4 I_diffuse = light.diffuse * material.diffuse * max(dot(N, L), 0.0);
    vec4 I_specular = light.specular  * material.specular * pow(max(dot(R,
                    V_vec), 0.0), material.shininess);

    vec4 I_total = I_ambient + I_diffuse + I_specular;

    /* reflect ray around normal from eye to surface */
    vec3 incident_eye = normalize(pos_eye);
    vec3 normal = normalize(n_eye);

    vec3 reflected = reflect(incident_eye, normal);
    // convert from eye to world space
    reflected = vec3(inverse(V) * vec4(reflected, 0.0));

    float ratio = 1.0 /1.3333;
    vec3 refracted = refract(incident_eye, normal, ratio);
    refracted = vec3(inverse(V) * vec4(refracted, 0.0));

    //out_Color = vec4(1,0,0,1);
    out_Color = I_total + 0.5*texture(cube_texture, reflected) +
        0.5*texture(cube_texture, refracted);
}
