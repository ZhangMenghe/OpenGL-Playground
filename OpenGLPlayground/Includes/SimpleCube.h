#ifndef SIMPLE_CUBE_H
#define SIMPLE_CUBE_H
#include <TextureRender.h>

class SimpleCube : public TextureRender
{
public:
	SimpleCube(const char* vertexPath, const char* fragmentPath,
			   const char* geometryPath = nullptr);
	void onInitial();
	void onDraw3D();
protected:
	glm::fvec3 _baseColor = glm::fvec3(1.0);
	virtual void postInitial();
	virtual void preDraw3D_CUBE();
	virtual void onDraw3D_CUBE();
	virtual void postDraw3D_CUBE();
};

#endif
