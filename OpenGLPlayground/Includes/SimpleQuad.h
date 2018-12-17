#ifndef SIMPLE_QUAD_H
#define SIMPLE_QUAD_H
#include <TextureRender.h>

class SimpleQuad : public TextureRender
{
public:
	SimpleQuad(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
	void onInitial();
protected:
	GLuint _texture_id;
};

#endif