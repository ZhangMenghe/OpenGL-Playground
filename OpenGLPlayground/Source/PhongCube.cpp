#include <GL/glew.h>
#include <string.h>
#include <PhongCube.h>
#include <Camera.h>
#include <glm/gtc/matrix_transform.hpp>

PhongCube::PhongCube(const char* vertexPath, const char* fragmentPath, const char* geometryPath)
	:SimpleCube(vertexPath, fragmentPath, geometryPath) {
}
void PhongCube::postInitial() {
	_lightColor = glm::fvec3(1.0, 1.0, 1.0);
	glm::vec3 diffuseColor = _lightColor * glm::vec3(0.5f); // decrease the influence
	glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // low influence

	_objColor = glm::fvec3(0.43, 0.545, 0.24);//1.0f, 0.5f, 0.31f
	_lightPos = glm::fvec3(1.2, 1.0, 2.0);
	
	shaderHelper->use();
	shaderHelper->setVec3("uLight.ambient_color", ambientColor);
	shaderHelper->setVec3("uLight.diffuse_color", diffuseColor);
	shaderHelper->setVec3("uLight.specular_color", _lightColor);
	
	_diffuse_tex_id = create2DTexture("Resources/cube_diffuse.png");
	shaderHelper->setInt("uMaterial.diffuse_sampler", 0);

	_specular_tex_id = create2DTexture("Resources/cube_specular.png");
	shaderHelper->setInt("uMaterial.specular_sampler", 1);

	shaderHelper->setFloat("uMaterial.shininess", 64.0f);

	/*shaderHelper->use();
	shaderHelper->setVec3("uLightColor", _lightColor);
	shaderHelper->setVec3("uObjectColor", _objColor);
	shaderHelper->setVec3("uLightPos", _lightPos);*/
}

void PhongCube::onDraw3D_CUBE() {
	SimpleCube::onDraw3D_CUBE();

	shaderHelper->setVec3("uEyePos", Camera::instance()->GetCameraPosition());
	shaderHelper->setVec3("uLight.position", _lightPos);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _diffuse_tex_id);

	// bind specular map
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _specular_tex_id);
}
