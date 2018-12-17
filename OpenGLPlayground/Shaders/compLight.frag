#version 330 core

out vec4 FragColor;
in vec3 vNormal, vFragPos;
in vec2 vTexcoord;

struct Light{
	vec3 position;

	vec3 ambient_color;
	vec3 diffuse_color;
	vec3 specular_color;
};
struct Material{
	sampler2D diffuse_sampler;
	sampler2D specular_sampler;
	float shininess;   
};

uniform vec3 uEyePos;
uniform Light uLight;
uniform Material uMaterial;

void main(){
	//ambient
	vec3 ambient = uLight.ambient_color * texture(uMaterial.diffuse_sampler, vTexcoord).rgb;

	//diffuse
	vec3 N = normalize(vNormal);
	vec3 L = normalize(uLight.position - vFragPos);
	float diff_term = max(dot(N, L), 0.0);
	vec3 diffuse = uLight.diffuse_color * diff_term * texture(uMaterial.diffuse_sampler, vTexcoord).rgb;

	//specular
	vec3 V = normalize(uEyePos - vFragPos);
	vec3 R = reflect(-L, N);
	float spec_term = pow(max(dot(V, R), 0.0), uMaterial.shininess);

	vec3 specular = uLight.specular_color * spec_term * texture(uMaterial.specular_sampler, vTexcoord).rgb;

	FragColor = vec4(vec3(ambient+diffuse+specular), 1.0);
}