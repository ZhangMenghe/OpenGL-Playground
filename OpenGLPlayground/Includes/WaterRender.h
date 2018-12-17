#ifndef WATER_RENDER_H
#define WATER_RENDER_H
#include <TextureRender.h>

class WaterRender : public TextureRender
{
public:
	WaterRender(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
	void onInitial();
	void onDraw3D();
	
private:
	GLuint _texture_id;
	static const int QUAD_GRID_SIZE = 40;
};

#endif