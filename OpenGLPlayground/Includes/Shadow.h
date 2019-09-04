#ifndef SHADOW_H
#define SHADOW_H
#include <vector>

#include <PrimitiveUtils.h>
#include <SimpleQuad.h>
#include <GLShaderHelper.h>
#include <Texture.h>
class ShadowRender {
	SimpleQuad *_quad;

	unsigned int _quadVAO, _planeVAO, _cubeVAO;
	unsigned int _depthFBO, _depthMap;

	GLShaderHelper *_depthShader,
				   *_objShader,//shader for scene objects
				   *_debugquadShader;//render depthbuffer to a debug quad
	
	const glm::vec3 lightPos = glm::vec3(-1.5f, 3.0f, -1.0f);
	bool RENDER_FROM_LIGHTSPACE = true;
	const float LIGHT_NEAR_PLANE = 1.0f, LIGHT_FAR_PLANE = 7.5f;
	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	Texture* _boxTexture;

	bool DRAW_DEBUG_QUAD = true;
	void init_shader();

	void render_debug();
	void render_to_texture(glm::mat4 projMat, glm::mat4 viewMat);
	void render_to_screen();
	void render_scene(GLShaderHelper* shader);
public:
	ShadowRender();
	void onInitial();
	void onDraw3D();
	void onDestroy();
	
};
#endif // !SHADOW_H

