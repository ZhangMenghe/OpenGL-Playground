#version 330 core
out vec4 FragColor;

/* Multiple bump coordinates for animated bump mapping */
in vec2 bumpCoord0, bumpCoord1, bumpCoord2;
in vec3 vBinormal, vTangent, vNormal, vView;

uniform sampler2D uSampler;
uniform samplerCube uSamplerCube;

//fresnel terms air to water
const float R0 = 0.02037;
const vec4 deepColor = vec4(0.0, 0.0, 0.1, 1.0);
const vec4 shallowColor = vec4(0.0, 0.5, 0.5, 1.0);
const float eta = 1.0/1.33;
void main(){
	vec3 N = normalize(vNormal);
	vec3 V = normalize(vView);
	float facing = 1- max(dot(V,N), 0.0);
	vec4 waterColor = mix(deepColor,shallowColor,facing);

	//animated bump mapping
  	vec4 n0 = texture(uSampler,bumpCoord0) *2 -1;
	vec4 n1 = texture(uSampler,bumpCoord1) *2 -1;
	vec4 n2 = texture(uSampler,bumpCoord2) *2 -1;
	vec3 nBump = normalize(n0.xyz + n1.xyz + n2.xyz);

	//tangent space-> world space(nbump->newN)
	mat3 BTN = mat3(vBinormal, vTangent, vNormal); 
	vec3 newN = BTN * nBump;
	newN= normalize(newN);

	//Reflection Mapping
    vec3 reflection = reflect(V,newN);
    vec4 reflecColor = texture(uSamplerCube, reflection);

	//fresnel:how much light reflects at glancing angle and how much refracts
  	float fastFresnel = R0 + (1-R0) * pow( (1-dot(V,newN)) , 5);

		
	vec3 refract = refract(-V, newN, eta);//air to water
	vec4 refraction = texture(uSamplerCube, refract);

	//FragColor = waterColor + reflecColor * fastFresnel + refraction * (1-fastFresnel);
	FragColor= vec4(.0, 0.2, 0.8, 1.0);
}