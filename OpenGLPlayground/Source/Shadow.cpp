#include <Shadow.h>
#include <GL/glew.h>
#include <Camera.h>
ShadowRender::ShadowRender(){
	glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_ALWAYS);
}
void ShadowRender::onInitial() {
	//Plane
	InitVertices(PLANE_VERTEX_NORMAL_TEXCOORD, 6, _planeVAO);
	// cubes
	InitVertices(CUBE_VERTEX_NORMAL_TEXCOORD, 36, _cubeVAO);
	//Debug Quad
	InitVertices2D(QUAD_VERTEX_TEXCOORD, 4, _quadVAO);

	//FBO
	InitFBO(_depthFBO, _depthMap, SHADOW_WIDTH, SHADOW_HEIGHT);

	//init shaders
	init_shader();
}

void ShadowRender::init_shader() {
	_depthShader = new GLShaderHelper("Shaders/shadow_depth.vert", "Shaders/shadow_depth.frag");
	_debugquadShader = new GLShaderHelper("Shaders/shadow_debug_quad.vert", "Shaders/shadow_debug_quad.frag");
	_objShader = new GLShaderHelper("Shaders/shadow_cube.vert", "Shaders/shadow_cube.frag");
	
	_boxTexture = new Texture("Resources/cube_diffuse.png");

	_objShader->use();
	_objShader->setInt("uSampler_depth", 0);
	_objShader->setInt("uSampler_tex", 1);

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
void ShadowRender::render_scene(GLShaderHelper* shader) {
	shader->use();

	//floor
	shader->setMat4("uModelMat", glm::mat4(1.0f));
	_objShader->setVec3("uBaseColor", glm::vec3(0.6f));
	glBindVertexArray(_planeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//cubes
	shader->setMat4("uModelMat", glm::translate(glm::mat4(1.0f), glm::vec3(.0f, 1.0f, .0f)));
	shader->setVec3("uBaseColor", glm::vec3(0.8f, 0.8f, .0f));
	glBindVertexArray(_cubeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

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

	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, _depthFBO);
		glClear(GL_DEPTH_BUFFER_BIT);
		render_scene(_depthShader);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void ShadowRender::render_to_screen() {
	// reset viewport
	int sw, sh;
	Camera::instance()->getScreenShape(sw, sh);
	glViewport(0, 0, sw, sh);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//config obj shader
	_objShader->use();
	_objShader->setMat4("uProjMat", Camera::instance()->getProjectionMatrix());
	_objShader->setMat4("uViewMat", Camera::instance()->GetViewMatrix());

	_objShader->setVec3("uViewPos", Camera::instance()->GetCameraPosition());
	_objShader->setVec3("uLightPos", lightPos);
	glm::mat4 lightProjection = glm::perspective(glm::radians(45.0f), (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, LIGHT_NEAR_PLANE, LIGHT_FAR_PLANE); // note that if you use a perspective projection matrix you'll have to change the light position as the current light position isn't enough to reflect the whole scene
	glm::mat4 lightOrthoProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, LIGHT_NEAR_PLANE, LIGHT_FAR_PLANE);

	glm::mat4 lightSpaceMatrix = lightOrthoProjection * glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
	_objShader->setMat4("uLightspaceMat", lightSpaceMatrix);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _depthMap);
	
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _boxTexture->GLTexture());
	render_scene(_objShader);
}
void ShadowRender::onDraw3D() {
	// 1. render depth of scene to texture
	if (RENDER_FROM_LIGHTSPACE) {
		glm::mat4 lightProjection = glm::perspective(glm::radians(45.0f), (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, LIGHT_NEAR_PLANE, LIGHT_FAR_PLANE); // note that if you use a perspective projection matrix you'll have to change the light position as the current light position isn't enough to reflect the whole scene
		glm::mat4 lightOrthoProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, LIGHT_NEAR_PLANE, LIGHT_FAR_PLANE);
		render_to_texture(lightOrthoProjection,
			glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0)));
	}
	else
		render_to_texture(Camera::instance()->getProjectionMatrix(), Camera::instance()->GetViewMatrix());

	
	//2. DEBUG DRAW
	//render_debug();
	// 2. render scene as normal using the generated depth/shadow map 
	render_to_screen();

	
		
	
}
void ShadowRender::onDestroy() {

}
