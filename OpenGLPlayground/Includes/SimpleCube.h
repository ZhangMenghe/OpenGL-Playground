#ifndef SIMPLE_CUBE_H
#define SIMPLE_CUBE_H
#include <TextureRender.h>

class SimpleCube : public TextureRender
{
public:
	SimpleCube(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
	void onInitial();
	void onDraw3D();
};

#endif
