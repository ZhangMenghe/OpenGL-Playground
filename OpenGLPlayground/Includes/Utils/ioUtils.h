#pragma once
#ifndef IO_UTIL_H
#define IO_UTIL_H

#include <fstream>
#include <iostream>

inline GLuint initVol3DTex(const char* filename, GLuint w, GLuint h, GLuint d){
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
#endif // !IO_UTIL_H
