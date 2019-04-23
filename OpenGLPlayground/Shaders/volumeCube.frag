#version 330 core
out vec4 FragColor;
in vec3 vTexcoord;
uniform sampler3D uSampler;
float scale = 1000.0;
float offset = 0;
void main(){
	//float intensity = scale * texture(uSampler, vTexcoord).r + offset;
	//gl_FragColor=vec4(intensity);
	gl_FragColor = texture(uSampler, vTexcoord);
}