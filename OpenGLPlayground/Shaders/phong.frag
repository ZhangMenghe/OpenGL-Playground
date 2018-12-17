#version 330 core

out vec4 FragColor;
in vec3 vNormal, vFragPos;

uniform vec3 uLightPos, uEyePos;
uniform vec3 uLightColor, uObjectColor;

const float ambientStrength = 0.1;
const float specularStrength = 0.5;
const float specularAlpha = 32;

void main(){
	//ambient
	vec3 ambient = ambientStrength * uLightColor;

	//diffuse
	vec3 N = normalize(vNormal);
	vec3 L = normalize(uLightPos - vFragPos);
	vec3 diffuse = max(dot(N, L), 0.0) * uLightColor;

	//specular
	vec3 V = normalize(uEyePos - vFragPos);
	vec3 R = reflect(-L, N);
	vec3 specular = specularStrength * pow(max(dot(V, R), 0.0), specularAlpha) * uLightColor;

	FragColor = vec4(vec3((ambient+diffuse+specular)*uObjectColor), 1.0);
}