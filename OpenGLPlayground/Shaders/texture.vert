#version 330 core

attribute vec3 aPosition;
attribute vec2 aTexCoord;

out vec2 vTexcoord;

void main(){
    vTexcoord = aTexCoord;
    gl_Position = vec4(aPosition, 1.0);
}
