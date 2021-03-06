#include <Shadow.h>
#include <GL/glew.h>
#include <Camera.h>
#include <glm/gtx/rotate_vector.hpp>

ShadowRender::ShadowRender(){
	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_ALWAYS);
	shadow_width = SHADOW_WIDTH; shadow_height = SHADOW_HEIGHT;
	lightPos = DEFAULT_LIGHT_POS;
	lightProjection = glm::perspective(glm::radians(45.0f), (GLfloat)shadow_width / (GLfloat)shadow_height, LIGHT_NEAR_PLANE, LIGHT_FAR_PLANE); // note that if you use a perspective projection matrix you'll have to change the light position as the current light position isn't enough to reflect the whole scene
	lightOrthoProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, LIGHT_NEAR_PLANE, LIGHT_FAR_PLANE);
	cube_modelmats.push_back(glm::translate(glm::mat4(1.0f), LOOKAT_CENTER) * glm::scale(glm::mat4(1.0), glm::vec3(2, 2, 2)));
	cube_modelmats_inv.push_back(glm::inverse(cube_modelmats[0]));
}
void ShadowRender::onInitial() {
	//Plane
	InitVertices(PLANE_VERTEX_NORMAL_TEXCOORD, 6, _planeVAO);
	// cubes
	InitVertices(CUBE_VERTEX_NORMAL_TEXCOORD, 36, _cubeVAO);
	//Debug Quad
	InitVertices2D(QUAD_VERTEX_TEXCOORD, 4, _quadVAO);

	//FBO
	InitFBO(_depthFBO, _depthMap, shadow_width, shadow_height);

	//init shaders
	init_shader();
}

void ShadowRender::init_shader() {
	_depthShader = new GLShaderHelper("Shaders/shadow_depth.vert", "Shaders/shadow_depth.frag");
	_debugquadShader = new GLShaderHelper("Shaders/shadow_debug_quad.vert", "Shaders/shadow_debug_quad.frag");
	_objShader = new GLShaderHelper("Shaders/shadow_cube.vert", "Shaders/shadow_cube.frag");
	_cubeSubShader = new GLShaderHelper("Shaders/cubeSub.vert", "Shaders/cubeSub.frag");
	
	_boxTexture = new Texture("Resources/cube_diffuse.png");

	_objShader->use();
	_objShader->setInt("uSampler_depth", 0);
	_objShader->setInt("uSampler_tex", 1);
	
	glm::mat4 lightSpaceMatrix = lightOrthoProjection * glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
	_objShader->setMat4("uLightspaceMat", lightSpaceMatrix);

	_cubeSubShader->use();
	//_cubeSubShader->setInt("uSampler_depth", 0);

	_cubeSubShader->setVec3("uPlane.p", glm::vec3(cube_modelmats_inv[0] * glm::vec4(plane_p, 1.0)));
	_cubeSubShader->setVec3("uPlane.normal", plane_normal);
	_cubeSubShader->setBool("uPlane.upwards", true);

	_cubeSubShader->setVec3("uSphere.center", glm::vec3(cube_modelmats_inv[0] * glm::vec4(sphere_c, 1.0)));
	_cubeSubShader->setFloat("uSphere.radius", sphere_radius);
	_cubeSubShader->setBool("uSphere.outside", true);

	_depthShader->use();
	
	if (RENDER_FROM_LIGHTSPACE) {
		_depthShader->setFloat("near_plane", LIGHT_NEAR_PLANE);
		_depthShader->setFloat("far_plane", LIGHT_FAR_PLANE);
	}
	else {
		float near_plane, far_plane;
		Camera::instance()->getCameraProjectionPlane(near_plane, far_plane);
		_depthShader->setFloat("near_plane", near_plane);
		_depthShader->setFloat("far_plane", far_plane);
	}
	_debugquadShader->use();

	if (RENDER_FROM_LIGHTSPACE) {
		_debugquadShader->setFloat("near_plane", LIGHT_NEAR_PLANE);
		_debugquadShader->setFloat("far_plane", LIGHT_FAR_PLANE);
	}
	else {
		float near_plane, far_plane;
		Camera::instance()->getCameraProjectionPlane(near_plane, far_plane);
		_debugquadShader->setFloat("near_plane", near_plane);
		_debugquadShader->setFloat("far_plane", far_plane);
	}
}
void ShadowRender::render_debug() {
	// reset viewport
	int sw, sh;
	Camera::instance()->getScreenShape(sw, sh);
	glViewport(0, 0, sw, sh);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_debugquadShader->use();
	_debugquadShader->setInt("depthMap", 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _depthMap);


	glBindVertexArray(_quadVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}
void ShadowRender::render_object(GLShaderHelper* shader) {
	shader->use();
	//cubes
	shader->setMat4("uModelMat", cube_modelmats[0]);
	shader->setVec3("uBaseColor", glm::vec3(0.8f, 0.8f, .0f));
	shader->setBool("uIsCut", true);
	glBindVertexArray(_cubeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void ShadowRender::render_scene(GLShaderHelper* shader) {
	shader->use();

	//floor
	shader->setMat4("uModelMat", glm::mat4(1.0f));
	shader->setVec3("uBaseColor", glm::vec3(0.6f));
	shader->setBool("uIsCut", false);
	glBindVertexArray(_planeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	
	//cutting plane
	//render_cutting_plane(shader);

	//shader->setMat4("uModelMat", glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, .0f, .0f)));
	//glBindVertexArray(_cubeVAO);
	//glDrawArrays(GL_TRIANGLES, 0, 36);

	//shader->setMat4("uModelMat", glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, .0f)));
	//glBindVertexArray(_cubeVAO);
	//glDrawArrays(GL_TRIANGLES, 0, 36);
}
void ShadowRender::render_to_texture(glm::mat4 projMat, glm::mat4 viewMat) {
	_depthShader->use();
	_depthShader->setMat4("uProjMat", projMat);
	_depthShader->setMat4("uViewMat", viewMat);

	glViewport(0, 0, shadow_width, shadow_height);
	glBindFramebuffer(GL_FRAMEBUFFER, _depthFBO);
		glClear(GL_DEPTH_BUFFER_BIT);
		render_object(_depthShader);
		//render_scene(_depthShader);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void ShadowRender::render_to_screen(GLShaderHelper* shader) {
	// reset viewport
	int sw, sh;
	Camera::instance()->getScreenShape(sw, sh);
	glViewport(0, 0, sw, sh);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//config obj shader
	shader->use();
	shader->setMat4("uProjMat", Camera::instance()->getProjectionMatrix());
	shader->setMat4("uViewMat", Camera::instance()->GetViewMatrix());
	shader->setVec3("uCamposObjSpace", glm::vec3(cube_modelmats_inv[0]*glm::vec4(Camera::instance()->GetCameraPosition(), 1.0)));
	
	if (RENDER_FROM_LIGHTSPACE) {
		shader->setVec3("uLightPos", lightPos);
	}
	/*else {
		shader->setMat4("uProjMat_inv", glm::inverse(Camera::instance()->getProjectionMatrix()));
		shader->setMat4("uMVMat_inv", glm::inverse(Camera::instance()->GetViewMatrix() * cube_modelmats[0]));
	}*/
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _depthMap);
	
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _boxTexture->GLTexture());
	render_object(shader);
	render_scene(shader);
}
void ShadowRender::onDrawLightSpace(){
	glEnable(GL_DEPTH_TEST);

	render_to_texture(lightOrthoProjection,
		glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0)));
	render_to_screen(_objShader);

	glDisable(GL_DEPTH_TEST);
}
void ShadowRender::onDrawCameraSpace(){
	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	render_to_texture(Camera::instance()->getProjectionMatrix(), Camera::instance()->GetViewMatrix());
	render_to_screen(_cubeSubShader);

	//glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
}

void ShadowRender::onDraw3D() {
	if (RENDER_FROM_LIGHTSPACE) onDrawLightSpace();
	else onDrawCameraSpace();
	if (DRAW_DEBUG_QUAD) render_debug();
}
void ShadowRender::render_cutting_plane(GLShaderHelper* shader) {
	shader->setMat4("uModelMat",
		glm::translate(glm::mat4(1.0), plane_p)*
		glm::orientation(plane_normal, glm::vec3(0, 0, 1)) *
		glm::scale(glm::mat4(1.0), glm::vec3(3, 3, 3)));
	shader->setVec3("uBaseColor", glm::vec3(0.2f, .0f, .0f));
	shader->setBool("uIsCut", false);
	if (!_cplaneVAO) {
		float vertices[] = {
			1.0f,1.0f,.0f,
			-1.0f,1.0f,.0f,
			-1.0f,-1.0f,.0f,

			-1.0f,-1.0f,.0f,
			1.0f,-1.0f,.0f,
			1.0f,1.0f,.0f,
		};
		unsigned int VBO = 0;
		glGenVertexArrays(1, &_cplaneVAO);
		glGenBuffers(1, &VBO);
		// fill buffer
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), vertices, GL_STATIC_DRAW);
		// link vertex attributes
		glBindVertexArray(_cplaneVAO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	glBindVertexArray(_cplaneVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	//glBindVertexArray(0);
}

void ShadowRender::onDestroy() {

}
