#ifndef WATER_RENDER_H
#define WATER_RENDER_H
#include <TextureRender.h>

class WaterRender : public TextureRender
{
public:
	WaterRender(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
	void onInitial();
	void onDraw3D();

	void ZoomIn() { _eyePos.y -= 5.0f; _eyePos.z = _eyePos.y; bEyeChange = true; }
	void ZoomOut() { _eyePos.y += 5.0f; _eyePos.z = _eyePos.y; bEyeChange = true;}
	void RotateView(glm::vec2 delta_move);
private:
	bool bEyeChange = true;
	glm::vec3 view_rotate = glm::vec3(.0f);
	glm::mat4 _cameraRot = glm::mat4(1.0f);
	static const int QUAD_GRID_SIZE = 40;
};

#endif