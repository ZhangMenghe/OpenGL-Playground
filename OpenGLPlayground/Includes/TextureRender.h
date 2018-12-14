#ifndef TEXTURE_RENDER_H
#define TEXTURE_RENDER_H
#include <GLShaderHelper.h>

class TextureRender
{
public:
	TextureRender(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
	virtual void onInitial();
	void onInitial(float* vertices, int verticeNum,
				   unsigned int* indices, int indiceNum, 
				   float* uvs);
	void onDraw();
	void onDraw3D();
	void onDestroy();
	void create2DTexture(const char* texture_file_name);
	void createCubeTexture(const char* path_posx, const char* path_negx,
						   const char* path_posy, const char* path_negy,
						   const char* path_posz, const char* path_negz);
	void setProjectionMatrix(glm::mat4 proj) { _projMat = proj;}
protected:
	float * _vertices;
	GLuint * _indices;
	float * _uvs;

	GLuint VAO, VBO[2], EBO;
	GLuint _texture_id, _skybox_id;
	GLShaderHelper *shaderHelper;

	GLuint _attrib_vertices;
	GLuint _attrib_uvs;

	int _vertice_num;
	int _indices_num;

	const glm::vec3 UP = glm::vec3(.0f, 1.0f, .0f);
	const glm::vec3 CENTER = glm::vec3(.0f);
	glm::vec3 _eyePos = glm::vec3(.0f, 100.0f, 140.0f);
	glm::mat4 _viewMat = glm::mat4();
	glm::mat4 _projMat = glm::mat4();

	void _initialize_buffers_static();
};

#endif