#ifndef TEXTURE_RENDER_H
#define TEXTURE_RENDER_H
#include "GLShaderHelper.h"
#include <vector>

class TextureRender{
public:
	TextureRender(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
	virtual void onInitial();
	void onInitial(float* vertices, int verticeNum,
				   unsigned int* indices, int indiceNum, 
				   float* uvs);
	void onDraw();
	void onDraw3D();
	void onDestroy();
	
	void setModelMatrix(glm::mat4 model) { _modelMat = model; }
	GLShaderHelper* getShaderHelper() { return shaderHelper; }

protected:
	float * _vertices;
	unsigned int * _indices;
	float * _uvs;

	unsigned int VAO, VBO[2], EBO;
	GLShaderHelper *shaderHelper;

	unsigned int _attrib_vertices;
	unsigned int _attrib_uvs;

	int _vertice_num;
	int _indices_num;

	glm::mat4 _modelMat;
	glm::vec3 view_rotate = glm::vec3(.0f);
	glm::mat4 _cameraRot = glm::mat4(1.0f);

	void _initialize_buffers_static();
	unsigned int create2DTexture(const char* texture_file_name);
	unsigned int createCubeTexture(const char** cube_files);
};

#endif