#version 330 core
layout (location = 0) in vec3 aPos;

// uniform mat4 uModelMat;
uniform mat4 uModelMat, uViewMat, uProjMat;

void main()
{
    // gl_Position = lightSpaceMatrix * uModelMat * vec4(aPos, 1.0);
    gl_Position = uProjMat * uViewMat * uModelMat * vec4(aPos, 1.0f);
}