#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string.h>
#include <TextureRender.h>
#include <glm/gtc/matrix_transform.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
TextureRender::TextureRender(const char* vertexPath, const char* fragmentPath, const char* geometryPath) {
	GLenum err = glewInit();
	// Test for OpenGL 3
	if (GLEW_VERSION_3_0){
		printf("GL version 3 supported \n");
	}
	shaderHelper = new GLShaderHelper(vertexPath, fragmentPath, geometryPath);
	_modelMat = _viewMat = _projMat = glm::mat4(1.0f);
}
void TextureRender::onInitial(){}
void TextureRender::onInitial(float* vertices, int verticeNum,
	unsigned int* indices, int indiceNum,
	float* uvs) {
	_vertice_num = verticeNum;	_indices_num = indiceNum;

	_vertices = vertices;
	_indices = indices;
	_uvs = uvs;

	_initialize_buffers_static();
}
void TextureRender::_initialize_buffers_static() {
	glEnable(GL_DEPTH_TEST);
	_attrib_vertices = glGetAttribLocation(shaderHelper->getShaderId(), "aPosition");
	_attrib_uvs = glGetAttribLocation(shaderHelper->getShaderId(), "aTexCoord");

	glGenVertexArrays(1, &VAO);
	glGenBuffers(2, VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, _vertice_num * 3 * sizeof(float), _vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(_attrib_vertices);
	glVertexAttribPointer(_attrib_vertices, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);


	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, _vertice_num * 2 * sizeof(GLuint), _uvs, GL_STATIC_DRAW);
	glEnableVertexAttribArray(_attrib_uvs);
	glVertexAttribPointer(_attrib_uvs, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);
	/*dynamic
	glBindBuffer(GL_ARRAY_BUFFER, _VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8, nullptr, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(_attrib_uvs);
	glVertexAttribPointer(_attrib_uvs, 2, GL_FLOAT, GL_FALSE, 0, 0);
	*/

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices_num * sizeof(GLuint), _indices, GL_STATIC_DRAW);
	
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
unsigned int TextureRender::createCubeTexture(const char** cube_files) {
	GLuint skyboxID;
	glGenTextures(1, &skyboxID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxID);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
											// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	int width, height, nrChannels;
	for (int i = 0; i < 6; i++) {
		unsigned char *data = stbi_load(cube_files[i], &width, &height, &nrChannels, 0);
		if (data)
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
	}
	return skyboxID;
}
unsigned int TextureRender::create2DTexture(const char* texture_file_name) {
	GLuint textureID;
	glGenTextures(1, &textureID);
	
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
											// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	unsigned char *data = stbi_load(texture_file_name, &width, &height, &nrChannels, 0);
	if (data){
		GLenum format;
		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, 
					 width, height, 0, format,
				     GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	stbi_image_free(data);
	return textureID;
}

void TextureRender::onDraw() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// render container
	shaderHelper->use();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, _indices_num, GL_UNSIGNED_INT, 0);
}

void TextureRender::onDraw3D() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shaderHelper->use();
	if (bViewChanged) {
		_viewMat = glm::lookAt(_eyePos, _eyePos+ _camera_front, UP);// *_cameraRot;
		bViewChanged = false;
	}

	shaderHelper->setMat4("uProjMat", _projMat);
	shaderHelper->setMat4("uViewMat", _viewMat);
	shaderHelper->setVec3("uEye", _eyePos);
	
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, _indices_num, GL_UNSIGNED_INT, 0);
}
void TextureRender::onDestroy() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(2, VBO);
	glDeleteBuffers(1, &EBO);
}

void TextureRender::RotateCamera(glm::fvec3 front_dir) {
	_camera_front = front_dir;
	bViewChanged = true;
}
void TextureRender::MoveCamera(glm::fvec3 move) {
	_eyePos += move; 
	bViewChanged = true; 
}