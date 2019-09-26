#ifndef PRIMITIVE_UTILS_H
#define PRIMITIVE_UTILS_H

#include <Config.h>`
//8*36
const float CUBE_VERTEX_NORMAL_TEXCOORD[288] = {
	// back face
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -0.5f, 0.0f, 0.0f, // bottom-left
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -0.5f, 0.5f, 0.5f, // top-right
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -0.5f, 0.5f, 0.0f, // bottom-right         
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -0.5f, 0.5f, 0.5f, // top-right
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -0.5f, 0.0f, 0.0f, // bottom-left
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -0.5f, 0.0f, 0.5f, // top-left
		// front face
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  0.5f, 0.0f, 0.0f, // bottom-left
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  0.5f, 0.5f, 0.0f, // bottom-right
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  0.5f, 0.5f, 0.5f, // top-right
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  0.5f, 0.5f, 0.5f, // top-right
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  0.5f, 0.0f, 0.5f, // top-left
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  0.5f, 0.0f, 0.0f, // bottom-left
		// left face
		-0.5f,  0.5f,  0.5f, -0.5f,  0.0f,  0.0f, 0.5f, 0.0f, // top-right
		-0.5f,  0.5f, -0.5f, -0.5f,  0.0f,  0.0f, 0.5f, 0.5f, // top-left
		-0.5f, -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, 0.0f, 0.5f, // bottom-left
		-0.5f, -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, 0.0f, 0.5f, // bottom-left
		-0.5f, -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
		-0.5f,  0.5f,  0.5f, -0.5f,  0.0f,  0.0f, 0.5f, 0.0f, // top-right
		// right face
		 0.5f,  0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 0.5f, 0.0f, // top-left
		 0.5f, -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 0.0f, 0.5f, // bottom-right
		 0.5f,  0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 0.5f, 0.5f, // top-right         
		 0.5f, -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 0.0f, 0.5f, // bottom-right
		 0.5f,  0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 0.5f, 0.0f, // top-left
		 0.5f, -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
		// bottom face
		-0.5f, -0.5f, -0.5f,  0.0f, -0.5f,  0.0f, 0.0f, 0.5f, // top-right
		 0.5f, -0.5f, -0.5f,  0.0f, -0.5f,  0.0f, 0.5f, 0.5f, // top-left
		 0.5f, -0.5f,  0.5f,  0.0f, -0.5f,  0.0f, 0.5f, 0.0f, // bottom-left
		 0.5f, -0.5f,  0.5f,  0.0f, -0.5f,  0.0f, 0.5f, 0.0f, // bottom-left
		-0.5f, -0.5f,  0.5f,  0.0f, -0.5f,  0.0f, 0.0f, 0.0f, // bottom-right
		-0.5f, -0.5f, -0.5f,  0.0f, -0.5f,  0.0f, 0.0f, 0.5f, // top-right
		// top face
		-0.5f,  0.5f, -0.5f,  0.0f,  0.5f,  0.0f, 0.0f, 0.5f, // top-left
		 0.5f,  0.5f , 0.5f,  0.0f,  0.5f,  0.0f, 0.5f, 0.0f, // bottom-right
		 0.5f,  0.5f, -0.5f,  0.0f,  0.5f,  0.0f, 0.5f, 0.5f, // top-right     
		 0.5f,  0.5f,  0.5f,  0.0f,  0.5f,  0.0f, 0.5f, 0.0f, // bottom-right
		-0.5f,  0.5f, -0.5f,  0.0f,  0.5f,  0.0f, 0.0f, 0.5f, // top-left
		-0.5f,  0.5f,  0.5f,  0.0f,  0.5f,  0.0f, 0.0f, 0.0f  // bottom-left       
};
//Plane
const float PLANE_VERTEX_NORMAL_TEXCOORD[48] = {
	// positions            // normals         // texcoords
	 25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
	-25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
	-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,

	 25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
	-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
	 25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,  25.0f, 10.0f
};

//Quad 2d
const float QUAD_VERTEX_TEXCOORD[20] = {
	// positions        // texture Coords
	-1.0f,  1.0f, 0.0f,  0.0f, 1.0f,
	-1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
	 1.0f,  1.0f, 0.0f,  1.0f, 1.0f,
	 1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
};

inline void InitVertices2D(const float* vertices, int num, GLuint& vao) {
	GLuint vbo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * num * 5, vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
}
inline void InitVertices(const float* vertices, int num, GLuint& vao) {
	GLuint vbo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 8 * num * sizeof(float), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}

inline void InitFBO(GLuint& fbo, GLuint& depthMap, int tex_width, int tex_height) {
	glGenFramebuffers(1, &fbo);
	//create depth as texture
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);

	//dynamic
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, tex_width, tex_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	//attach texture to fbo's depth buffer
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	//no need the color buffer, explicityly no such buffer
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
#endif