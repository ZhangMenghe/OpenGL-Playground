#include <GL/glew.h>
#include <string.h>
#include <PhongCube.h>
#include <glm/gtc/matrix_transform.hpp>

PhongCube::PhongCube(const char* vertexPath, const char* fragmentPath, const char* geometryPath)
	:SimpleCube(vertexPath, fragmentPath, geometryPath) {
}
void PhongCube::onInitial() {
	SimpleCube::onInitial();
	_lightColor = glm::fvec3(1.0, 1.0, 1.0);
	_objColor = glm::fvec3(0.43, 0.545, 0.24);//1.0f, 0.5f, 0.31f
	_lightPos = glm::fvec3(1.2, 1.0, 2.0);
	_modelMat = glm::mat4(1.0f);

	shaderHelper->use();
	shaderHelper->setVec3("uLightColor", _lightColor);
	shaderHelper->setVec3("uObjectColor", _objColor);
	shaderHelper->setVec3("uLightPos", _lightPos);
}

void PhongCube::onDraw3D() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (bViewChanged) {
		_viewMat = glm::lookAt(_eyePos, _eyePos + _camera_front, UP);
		bViewChanged = false;
	}

	shaderHelper->setMat4("uProjMat", _projMat);
	shaderHelper->setMat4("uViewMat", _viewMat);
	shaderHelper->setMat4("uModelMat", _modelMat);
	shaderHelper->setVec3("uEyePos", _eyePos);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
