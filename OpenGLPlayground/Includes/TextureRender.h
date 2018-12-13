#ifndef TEXTURE_RENDER_H
#define TEXTURE_RENDER_H
#include <GLShaderHelper.h>

class TextureRender
{
public:
	TextureRender(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
	virtual void onInitial();
	void onInitial(const float* vertices, int verticeNum,
				   const unsigned int* indices, int indiceNum, 
				   const float* uvs);
	void onDraw();
	void onDestroy();
	void setTexture(const char* texture_file_name);

protected:
	float * _vertices;
	GLuint * _indices;
	float * _uvs;

	GLuint VAO, VBO[2], EBO;
	GLuint _texture_id;
	GLShaderHelper *shaderHelper;

	GLuint _attrib_vertices;
	GLuint _attrib_uvs;

	int _vertice_num;
	int _indices_num;

	void _initialize_buffers_static();
};

#endif