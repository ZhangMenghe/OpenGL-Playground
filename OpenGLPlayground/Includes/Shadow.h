#ifndef SHADOW_H
#define SHADOW_H
#include <vector>

#include <PrimitiveUtils.h>
#include <SimpleQuad.h>
#include <GLShaderHelper.h>
#include <Texture.h>
class ShadowRender {
	SimpleQuad *_quad;

	unsigned int _quadVAO, _planeVAO, _cubeVAO, _cplaneVAO = 0;
	unsigned int _depthFBO, _depthMap;
	unsigned int shadow_width, shadow_height;

	std::vector<glm::mat4> cube_modelmats, cube_modelmats_inv;

	//lighting
	glm::vec3 lightPos;
	glm::mat4 lightProjection, lightOrthoProjection;
	GLShaderHelper *_depthShader,
				   *_objShader,//shader for scene objects
				   *_cubeSubShader,//shader for scene object with 	
				   *_debugquadShader;//render depthbuffer to a debug quad
	Texture* _boxTexture;

	glm::vec3 plane_p = LOOKAT_CENTER, plane_normal = glm::vec3(1.0f, .0f, .0f);

	void init_shader();
	void render_debug();
	void render_cutting_plane(GLShaderHelper* shader);

	void render_to_texture(glm::mat4 projMat, glm::mat4 viewMat);
	void render_to_screen(GLShaderHelper* shader);
	void render_scene(GLShaderHelper* shader);
	void render_object(GLShaderHelper* shader);
public:
	ShadowRender();
	void onInitial();
	void onDraw3D();
	void onDestroy();
	
};
#endif // !SHADOW_H

