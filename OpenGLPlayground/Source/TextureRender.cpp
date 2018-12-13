#include <GL/glew.h>
#include <string.h>
#include <TextureRender.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
TextureRender::TextureRender(const char* vertexPath, const char* fragmentPath, const char* geometryPath) {
	GLenum err = glewInit();
	// Test for OpenGL 3
	if (GLEW_VERSION_3_0){
		printf("GL version 3 supported \n");
	}
	shaderHelper = new GLShaderHelper(vertexPath, fragmentPath, geometryPath);
}
void TextureRender::onInitial() {}
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

void TextureRender::setTexture(const char* texture_file_name) {
	glGenTextures(1, &_texture_id);
	glBindTexture(GL_TEXTURE_2D, _texture_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
											// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	unsigned char *data = stbi_load(texture_file_name, &width, &height, &nrChannels, 0);
	if (data){
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	stbi_image_free(data);

	shaderHelper->use();
	shaderHelper->setInt("uSampler", 0);
}
void TextureRender::onDraw() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// bind textures on corresponding texture units
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texture_id);

	// render container
	shaderHelper->use();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, _indices_num, GL_UNSIGNED_INT, 0);
}
void TextureRender::onDestroy() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(2, VBO);
	glDeleteBuffers(1, &EBO);
}