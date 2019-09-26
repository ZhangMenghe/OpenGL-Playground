#ifndef SHADOW_H
#define SHADOW_H
#include <vector>

#include <PrimitiveUtils.h>
#include <SimpleQuad.h>
#include <GLShaderHelper.h>
#include <Texture.h>
class ShadowRender {
	glm::vec3 oriViewPos;
	SimpleQuad *_quad;

	unsigned int _quadVAO, _planeVAO, _cubeVAO, _cplaneVAO = 0;
	unsigned int _depthFBO, _depthMap;
	unsigned int shadow_width, shadow_height;

	glm::vec3 lightPos;
	glm::mat4 lightProjection, lightOrthoProjection;
	GLShaderHelper *_depthShader,
				   *_objShader,//shader for scene objects
				   *_cubeSubShader,//shader for scene object with 	
				   *_debugquadShader;//render depthbuffer to a debug quad
	Texture* _boxTexture;
	glm::vec3 plane_p = LOOKAT_CENTER, plane_normal = glm::vec3(.0f, -1.0f, .0f);
	std::vector<glm::vec3> STANDARD_QUAD{ glm::vec3(-1,-1,0),glm::vec3(-1,1,0), glm::vec3(1,1,0), glm::vec3(1,-1,0) };
	std::vector<glm::mat4> cube_model_mats;
	std::vector<glm::mat4> model_mat_inv;
	void init_shader();
	void render_debug();
	void render_to_texture(glm::mat4 projMat, glm::mat4 viewMat);
	void render_to_screen(GLShaderHelper* shader);
	void render_scene(GLShaderHelper* shader);
	void draw_cutting_plane();
public:
	ShadowRender();
	void onInitial();
	void onDraw3D();
	void onDestroy();
	
};
#endif // !SHADOW_H

