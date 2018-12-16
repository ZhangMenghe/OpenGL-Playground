#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec2 vTexcoord;
uniform mat4 uViewMat;
uniform mat4 uProjMat;

void main(){
    vTexcoord = aTexCoord;
    gl_Position = uProjMat * uViewMat  * vec4(aPos, 1.0f);
}
