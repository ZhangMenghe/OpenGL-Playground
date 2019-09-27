#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 uModelMat, uViewMat, uProjMat;
uniform vec3 uCamposObjSpace;

out VS_OUT {
	// vec3 camposObjSpace;
	vec3 raydir;
	vec3 screenPos;
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    // mat4 uMVMat_inv;
} vs_out;

void main(){
	// vs_out.camposObjSpace = uCamposObjSpace;//vec3(inverse(uModelMat) *vec4(uViewPos, 1.0));
	vs_out.raydir = aPos - uCamposObjSpace;
	vs_out.FragPos = vec3(uModelMat * vec4(aPos, 1.0f));

	vec4 screen_pos = uProjMat * uViewMat * vec4(vs_out.FragPos, 1.0);
	vs_out.screenPos = screen_pos.xyw;

	vs_out.Normal = transpose(inverse(mat3(uModelMat))) * aNormal;
	vs_out.TexCoords = aTexCoord;
	// vs_out.uMVMat_inv = inverse(uViewMat * uModelMat);
    gl_Position = screen_pos;
}