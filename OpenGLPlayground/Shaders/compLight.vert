#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec2 vTexcoord;
out vec3 vNormal, vFragPos;
uniform mat4 uModelMat, uViewMat, uProjMat;

void main(){
	vTexcoord = aTexCoord;
    vFragPos = vec3(uModelMat * vec4(aPos, 1.0));
	vNormal =  mat3(transpose(inverse(uModelMat))) * aNormal;
    gl_Position = uProjMat * uViewMat  * vec4(vFragPos, 1.0);
}
