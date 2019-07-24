#ifndef RAY_TRACER_H
#define RAY_TRACER_H
#include <TextureRender.h>
class RayTracer:public TextureRender {
public:
	RayTracer(const char* vertexPath, const char* fragmentPath,
		const char* geometryPath = nullptr);
	void onInitial();
	void onDraw();

	void setLightPos(glm::vec3 pos){}
};
#endif // !RAY_TRACER_H

