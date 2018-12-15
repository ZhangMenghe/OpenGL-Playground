#ifndef TEXTURE_RENDER_H
#define TEXTURE_RENDER_H
#include <GLShaderHelper.h>
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
	void create2DTexture(const char* texture_file_name);
	
	void setProjectionMatrix(glm::mat4 proj) { _projMat = proj;}

	void MoveCamera(glm::fvec3 move);
	void RotateCamera(glm::fvec3 front_dir);

protected:
	float * _vertices;
	unsigned int * _indices;
	float * _uvs;

	unsigned int VAO, VBO[2], EBO;
	unsigned int _texture_id, _skybox_id;
	GLShaderHelper *shaderHelper;

	unsigned int _attrib_vertices;
	unsigned int _attrib_uvs;

	int _vertice_num;
	int _indices_num;

	bool bViewChanged = true;
	const glm::vec3 UP = glm::vec3(.0f, 1.0f, .0f);
	glm::fvec3 _camera_front = glm::fvec3(.0, .0, -1.0f);
	glm::vec3 _eyePos = glm::vec3(.0f, 50.0, 100.0f);
	glm::mat4 _viewMat = glm::mat4();
	glm::mat4 _projMat = glm::mat4();
	glm::vec3 view_rotate = glm::vec3(.0f);
	glm::mat4 _cameraRot = glm::mat4(1.0f);

	void _initialize_buffers_static();
	void createCubeTexture(const char** cube_files);
};

#endif