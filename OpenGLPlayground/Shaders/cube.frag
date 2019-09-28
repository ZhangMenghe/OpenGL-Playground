#version 330 core
out vec4 FragColor;
uniform vec3 uBaseColor;

void main(){
	FragColor = vec4(uBaseColor, 1.0);
}
