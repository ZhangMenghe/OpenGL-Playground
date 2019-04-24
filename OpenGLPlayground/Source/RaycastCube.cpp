#include <GL/glew.h>
#include <string.h>
#include <RaycastCube.h>
#include <Camera.h>
#include <glm/gtc/matrix_transform.hpp>
#include <fstream>
#include <iostream>
#include <Utils/ioUtils.h>
RaycastCube::RaycastCube(const char* vertexPath, const char* fragmentPath, const char* geometryPath)
	:SimpleCube(vertexPath, fragmentPath, geometryPath) {
}
void RaycastCube::onInitial() {
	_vertice_num = 8;
	glEnable(GL_DEPTH_TEST);

	float dx = 0.5f / m_uImageWidth;
	float dy = 0.5f / m_uImageHeight;
	float dz = 0.5f / m_uImageCount;

	float x0 = 0.0f + dx;
	float x1 = 1.0f - dx;
	float y0 = 0.0f + dy;
	float y1 = 1.0f - dy;
	float z0 = 0.0f + dz;
	float z1 = 1.0f - dz;

	GLfloat Vertex[] = {//World					//Color
						-0.5f,-0.5f,0.5f,		x0, y0, z1, //0.0f,0.0f,0.0f,	//v0
						0.5f,-0.5f,0.5f,		x1,y0,z1, //1.0f,0.0f,0.0f,	//v1
						0.5f,0.5f,0.5f,			x1, y1, z1,//1.0f,1.0f,0.0f,	//v2
						-0.5f,0.5f,0.5f,		x0,y1,z1, //0.0f,1.0f,0.0f,	//v3
						-0.5f,-0.5f,-0.5f,		x0,y0,z0,//0.0f,0.0f,1.0f,	//v4
						0.5f,-0.5f,-0.5f,		x1,y0,z0,//1.0f,0.0f,1.0f,	//v5
						0.5f,0.5f,-0.5f,		x1,y1,z0, //1.0f,1.0f,1.0f,	//v6
						-0.5f,0.5f,-0.5f,		x0,y1,z0//0.0f,1.0f,1.0f,	//v7
	};

	GLuint Indices[] = { 0,1,2,0,2,3,	//front
						4,7,6,4,6,5,	//back
						4,0,3,4,3,7,	//left
						1,5,6,1,6,2,	//right
						3,2,6,3,6,7,	//top
						4,5,1,4,1,0,	//bottom
	};

	glGenBuffers(1, VBO);
	glGenBuffers(1, &EBO);

	// bind buffer for positions and copy data into buffer
	// GL_ARRAY_BUFFER is the buffer type we use to feed attributes
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	// feed the buffer, and let OpenGL know that we don't plan to
	// change it (STATIC) and that it will be used for drawing (DRAW)
	glBufferData(GL_ARRAY_BUFFER, 48 * sizeof(GL_FLOAT), Vertex, GL_STATIC_DRAW);

	//Set the index array
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(GL_UNSIGNED_INT), Indices, GL_STATIC_DRAW);



	//Generate the VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// bind buffer for positions and copy data into buffer
	// GL_ARRAY_BUFFER is the buffer type we use to feed attributes
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Unbind the vertex array	
	glBindVertexArray(0);


	//Disable Buffers and vertex attributes
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	postInitial();
}


GLuint initTransTex() {
	//prepare data
	size_t width = 128;
	GLubyte *data = new GLubyte[4*width];
	std::vector<glm::vec4> color_{ glm::vec4(1,0,0,1), glm::vec4(0,1,0,1) };

	int index = color_.size() - 1;
	for (int i = 0; i < width; ++i)
	{
		int   coli = (int)(index * (float)i / width);
		float colt = (index * (float)i / width) - coli;
		data[i * 4 + 0] = (unsigned char)(255.0 * (color_[coli].x*(1.0f - colt) + color_[coli + 1].x*colt));
		data[i * 4 + 1] = (unsigned char)(255.0 * (color_[coli].y*(1.0f - colt) + color_[coli + 1].y*colt));
		data[i * 4 + 2] = (unsigned char)(255.0 * (color_[coli].z*(1.0f - colt) + color_[coli + 1].z*colt));
		data[i * 4 + 3] = 255;
	}

	GLuint tex_id;
	glGenTextures(1, &tex_id);
	// bind 3D texture target
	glBindTexture(GL_TEXTURE_1D, tex_id);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// pixel transfer happens here from client to OpenGL server
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	//glTexImage3D(GL_TEXTURE_3D, 0, GL_INTENSITY, w, h, d, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, data);
	glTexImage1D(GL_TEXTURE_1D, 0, GL_INTENSITY, 4*width, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, data);

	return tex_id;
}
void RaycastCube::postInitial() {
	m_tex_3d_id = initVol3DTex("head256x256x109", m_uImageWidth, m_uImageHeight, m_uImageCount);
	m_tex_trans_id = initTransTex();
}
void RaycastCube::preDraw3D_CUBE() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_3D, m_tex_3d_id);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_1D, m_tex_trans_id);

	shaderHelper->use();

	shaderHelper->setMat4("uProjMat", Camera::instance()->getProjectionMatrix());
	shaderHelper->setMat4("uViewMat", Camera::instance()->GetViewMatrix());

	glm::mat4 sliceModel;
	//sliceModel = glm::translate(sliceModel, glm::vec3(0.0f, 0.0f, 0.0f));
	//sliceModel = glm::rotate(sliceModel, (float)glfwGetTime() * 30, glm::vec3(0.0f, 1.0f, 0.0f));
	sliceModel = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, -1.0f, 0.5f));
	shaderHelper->setMat4("uModelMat", sliceModel);

	shaderHelper->setInt("uSampler_tex", 0);
	shaderHelper->setInt("uSampler_trans", 1);
	shaderHelper->setVec3("uEyePos", Camera::instance()->GetCameraPosition());
	shaderHelper->setFloat("sample_step_inverse", 200.0f);
	shaderHelper->setFloat("val_threshold", 0.5f);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//glBindVertexArray(0);
}
void RaycastCube::onDraw3D_CUBE() {}
void RaycastCube::postDraw3D_CUBE() {}