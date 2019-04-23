#include <GL/glew.h>
#include <string.h>
#include <volumeCube.h>
#include <Camera.h>
#include <glm/gtc/matrix_transform.hpp>
#include <fstream>
#include <iostream>
VolumeCube::VolumeCube(const char* vertexPath, const char* fragmentPath, const char* geometryPath)
	:SimpleCube(vertexPath, fragmentPath, geometryPath) {
}
void VolumeCube::onInitial() {
	m_VAOs = new GLuint[m_uImageCount];
	for (int i = 0; i < m_uImageCount; i++)
	{
		float mappedZVal = -1.0f + 2.0f * (float)i / 109.0f;

		float zTex = (float)mappedZVal + 1.0f / 2.0f;

		float vertices[] = {
			// positions		// texture coords
			-0.5f,  -0.5f, mappedZVal,	0.0f, 0.0f, zTex,   // top right
			0.5f, -0.5f, mappedZVal,	1.0f, 0.0f, zTex,  // bottom right
			0.5f, 0.5f, mappedZVal,		1.0f, 1.0f, zTex,  // bottom left
			-0.5f,  0.5f, mappedZVal,	0.0f, 1.0f,  zTex  // top left
		};

		unsigned int VBO, EBO;
		unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
		};

		glGenVertexArrays(1, &m_VAOs[i]);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray((GLuint)m_VAOs[i]);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*6, indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);
	}
	postInitial();
}

GLuint initVol3DTex(const char* filename, GLuint w, GLuint h, GLuint d)
{
	GLuint g_volTexObj;
	FILE *fp;
	size_t size = w * h * d, result;
	GLubyte *data = new GLubyte[size];			  // 8bit
	errno_t err;
	if ((err = fopen_s(&fp, filename, "rb")) != 0) {
		std::cout << "Error: opening .raw file failed" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		std::cout << "OK: open .raw file successed" << std::endl;
	}
	result = fread(data, sizeof(char), size, fp);
	if (result != size)
	{
		std::cout << "Error: read .raw file failed" << std::endl;
		exit(1);
	}
	else
	{
		std::cout << "OK: read .raw file successed" << std::endl;
	}
	fclose(fp);

	glGenTextures(1, &g_volTexObj);
	// bind 3D texture target
	glBindTexture(GL_TEXTURE_3D, g_volTexObj);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);
	// pixel transfer happens here from client to OpenGL server
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage3D(GL_TEXTURE_3D, 0, GL_INTENSITY, w, h, d, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, data);

	delete[]data;
	std::cout << "volume texture created" << std::endl;
	return g_volTexObj;
}

void VolumeCube::postInitial() {
	m_puTextureIDs = new GLuint[m_uImageCount];
	m_puTextureIDs[0] = initVol3DTex("head256x256x109", m_uImageWidth, m_uImageHeight, m_uImageCount);
	/*std::ifstream file("head256x256x109", std::ifstream::binary);

	std::string fileName;

	// Holds the texture IDs.
	m_puTextureIDs = new GLuint[m_uImageCount];

	// Holds the luminance buffer
	char* chBuffer = new char[m_uImageWidth * m_uImageHeight * m_uImageCount];

	char* chRGBABuffer = new char[m_uImageWidth * m_uImageHeight * m_uImageCount * 4];

	glGenTextures(1, &m_puTextureIDs[0]);

	file.read(chBuffer, m_uImageWidth * m_uImageHeight * m_uImageCount);

	glBindTexture(GL_TEXTURE_3D, m_puTextureIDs[0]);

	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


	for (int nIndx = 0; nIndx < m_uImageWidth * m_uImageHeight * m_uImageCount; ++nIndx)
	{
		chRGBABuffer[nIndx * 4] = chBuffer[nIndx];
		chRGBABuffer[nIndx * 4 + 1] = chBuffer[nIndx];
		chRGBABuffer[nIndx * 4 + 2] = chBuffer[nIndx];
		chRGBABuffer[nIndx * 4 + 3] = 255;
		if (chBuffer[nIndx] < 20)
		{
			chRGBABuffer[nIndx * 4 + 3] = 0;
		}
	}

	glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, m_uImageWidth, m_uImageHeight, m_uImageCount, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, chRGBABuffer);
	glBindTexture(GL_TEXTURE_3D, 0);

	delete[] chBuffer;
	delete[] chRGBABuffer;*/
}
void VolumeCube::preDraw3D_CUBE() {
	for (int i = 0; i < m_uImageCount; i++)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_3D, m_puTextureIDs[0]);

		shaderHelper->use();

		shaderHelper->setMat4("uProjMat", Camera::instance()->getProjectionMatrix());
		shaderHelper->setMat4("uViewMat", Camera::instance()->GetViewMatrix());

		glm::mat4 sliceModel;
		//sliceModel = glm::translate(sliceModel, glm::vec3(0.0f, 0.0f, 0.0f));
		//sliceModel = glm::rotate(sliceModel, (float)glfwGetTime() * 30, glm::vec3(0.0f, 1.0f, 0.0f));
		sliceModel = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, -1.0f, 0.5f));
		shaderHelper->setMat4("uModelMat", sliceModel);
		
		shaderHelper->setInt("uSampler", 0);
		glBindVertexArray(m_VAOs[i]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}
void VolumeCube ::onDraw3D_CUBE() {}
void VolumeCube ::postDraw3D_CUBE(){}