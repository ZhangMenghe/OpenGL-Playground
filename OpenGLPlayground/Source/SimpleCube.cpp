#include <GL/glew.h>
#include <string.h>
#include <SimpleCube.h>
#include <Camera.h>
#include <glm/gtc/matrix_transform.hpp>
SimpleCube::SimpleCube(const char* vertexPath, const char* fragmentPath, 
					   const char* geometryPath)
	:TextureRender(vertexPath, fragmentPath, geometryPath) {
}
void SimpleCube::onInitial() {
	_eyePos = glm::vec3(0.0f, 0.0f, 3.0f);
	_vertice_num = 8;

	glEnable(GL_DEPTH_TEST);

	float vertices[] = {
		-0.5f,-0.5f,-0.5f,0.0f,0.0f,-1.0f,0.0f,0.0f,
		0.5f,-0.5f,-0.5f,0.0f,0.0f,-1.0f,1.0f,0.0f,
		0.5f,0.5f,-0.5f,0.0f,0.0f,-1.0f,1.0f,1.0f,
		0.5f,0.5f,-0.5f,0.0f,0.0f,-1.0f,1.0f,1.0f,
		-0.5f,0.5f,-0.5f,0.0f,0.0f,-1.0f,0.0f,1.0f,
		-0.5f,-0.5f,-0.5f,0.0f,0.0f,-1.0f,0.0f,0.0f,
		-0.5f,-0.5f,0.5f,0.0f,0.0f,1.0f,0.0f,0.0f,
		0.5f,-0.5f,0.5f,0.0f,0.0f,1.0f,1.0f,0.0f,
		0.5f,0.5f,0.5f,0.0f,0.0f,1.0f,1.0f,1.0f,
		0.5f,0.5f,0.5f,0.0f,0.0f,1.0f,1.0f,1.0f,
		-0.5f,0.5f,0.5f,0.0f,0.0f,1.0f,0.0f,1.0f,
		-0.5f,-0.5f,0.5f,0.0f,0.0f,1.0f,0.0f,0.0f,
		-0.5f,0.5f,0.5f,-1.0f,0.0f,0.0f,1.0f,0.0f,
		-0.5f,0.5f,-0.5f,-1.0f,0.0f,0.0f,1.0f,1.0f,
		-0.5f,-0.5f,-0.5f,-1.0f,0.0f,0.0f,0.0f,1.0f,
		-0.5f,-0.5f,-0.5f,-1.0f,0.0f,0.0f,0.0f,1.0f,
		-0.5f,-0.5f,0.5f,-1.0f,0.0f,0.0f,0.0f,0.0f,
		-0.5f,0.5f,0.5f,-1.0f,0.0f,0.0f,1.0f,0.0f,
		0.5f,0.5f,0.5f,1.0f,0.0f,0.0f,1.0f,0.0f,
		0.5f,0.5f,-0.5f,1.0f,0.0f,0.0f,1.0f,1.0f,
		0.5f,-0.5f,-0.5f,1.0f,0.0f,0.0f,0.0f,1.0f,
		0.5f,-0.5f,-0.5f,1.0f,0.0f,0.0f,0.0f,1.0f,
		0.5f,-0.5f,0.5f,1.0f,0.0f,0.0f,0.0f,0.0f,
		0.5f,0.5f,0.5f,1.0f,0.0f,0.0f,1.0f,0.0f,
		-0.5f,-0.5f,-0.5f,0.0f,-1.0f,0.0f,0.0f,1.0f,
		0.5f,-0.5f,-0.5f,0.0f,-1.0f,0.0f,1.0f,1.0f,
		0.5f,-0.5f,0.5f,0.0f,-1.0f,0.0f,1.0f,0.0f,
		0.5f,-0.5f,0.5f,0.0f,-1.0f,0.0f,1.0f,0.0f,
		-0.5f,-0.5f,0.5f,0.0f,-1.0f,0.0f,0.0f,0.0f,
		-0.5f,-0.5f,-0.5f,0.0f,-1.0f,0.0f,0.0f,1.0f,
		-0.5f,0.5f,-0.5f,0.0f,1.0f,0.0f,0.0f,1.0f,
		0.5f,0.5f,-0.5f,0.0f,1.0f,0.0f,1.0f,1.0f,
		0.5f,0.5f,0.5f,0.0f,1.0f,0.0f,1.0f,0.0f,
		0.5f,0.5f,0.5f,0.0f,1.0f,0.0f,1.0f,0.0f,
		-0.5f,0.5f,0.5f,0.0f,1.0f,0.0f,0.0f,0.0f,
		-0.5f,0.5f,-0.5f,0.0f,1.0f,0.0f,0.0f
	};

	_vertices = vertices;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO[0]);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	postInitial();
}
void SimpleCube::postInitial() {
	shaderHelper->use();
	shaderHelper->setVec3("uBaseColor", _baseColor);
}
void SimpleCube::onDraw3D() {
	preDraw3D_CUBE();
	onDraw3D_CUBE();
	postDraw3D_CUBE();
}
void SimpleCube::preDraw3D_CUBE() {

	shaderHelper->use();
}
void SimpleCube::onDraw3D_CUBE() {
	if (bViewChanged) {
		_viewMat = glm::lookAt(_eyePos, _eyePos + _camera_front, UP);
		bViewChanged = false;
	}
	shaderHelper->setMat4("uModelMat", _modelMat);
	shaderHelper->setMat4("uProjMat", Camera::instance()->getProjectionMatrix());
	shaderHelper->setMat4("uViewMat", Camera::instance()->GetViewMatrix());
}
void SimpleCube::postDraw3D_CUBE() {
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}