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
	unsigned int shadow_width, shadow_height;

	glm::vec3 lightPos;
	glm::mat4 lightProjection, lightOrthoProjection;
	GLShaderHelper *_depthShader,
				   *_objShader,//shader for scene objects
				   *_debugquadShader;//render depthbuffer to a debug quad
	Texture* _boxTexture;


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
