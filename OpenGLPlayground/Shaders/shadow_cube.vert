#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 uModelMat, uViewMat, uProjMat, uLightspaceMat;

out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} vs_out;


void main(){
	vs_out.FragPos = vec3(uModelMat * vec4(aPos, 1.0f));
	vs_out.Normal = transpose(inverse(mat3(uModelMat))) * aNormal;
	vs_out.TexCoords = aTexCoord;
	vs_out.FragPosLightSpace = uLightspaceMat * vec4(vs_out.FragPos, 1.0);

    gl_Position = uProjMat * uViewMat * vec4(vs_out.FragPos, 1.0);
}
