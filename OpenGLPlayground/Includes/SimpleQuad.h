#ifndef SIMPLE_QUAD_H
#define SIMPLE_QUAD_H
#include <TextureRender.h>

class SimpleQuad : public TextureRender
{
public:
	SimpleQuad(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
	void onInitial();
	void setTexture(const char* tex_path) {
		_texture_id = create2DTexture(tex_path);
	}
protected:
	unsigned int _texture_id;
};

#endif