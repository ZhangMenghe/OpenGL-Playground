#version 330 core
out vec4 FragColor;
in vec2 TexCoords;

uniform vec3 uBaseColor;
uniform sampler2D uSampler_tex;
void main(){
	FragColor = vec4(texture(uSampler_tex,TexCoords).rgb, 1.0); 
	//FragColor = vec4(uBaseColor, 1.0);
}
