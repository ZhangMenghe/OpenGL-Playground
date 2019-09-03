#include <GL/glew.h>
#include <string.h>
#include <SimpleQuad.h>
SimpleQuad::SimpleQuad(const char* vertexPath, const char* fragmentPath, const char* geometryPath)
	:TextureRender(vertexPath, fragmentPath, geometryPath){
}
void SimpleQuad::onInitial() {
	float vertices[] = {
		0.5f,  0.5f, 0.0f, // top right
		0.5f, -0.5f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,// bottom left
		-0.5f,  0.5f, 0.0f // top left 
	};
	float uvs[] = {
		1.0f, 1.0f, //top right
		1.0f, 0.0f, // bottom right
		0.0f, 0.0f, // bottom left
		0.0f, 1.0f  // top left 
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
	TextureRender::onInitial(vertices, 4, indices, 6, uvs);
	shaderHelper->use();
	shaderHelper->setInt("uSampler", 0);
}
