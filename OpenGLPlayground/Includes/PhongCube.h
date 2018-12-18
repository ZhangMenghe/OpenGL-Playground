#ifndef PHONG_CUBE_H
#define PHONG_CUBE_H
#include <SimpleCube.h>

class PhongCube : public SimpleCube
{
public:
	PhongCube(const char* vertexPath, const char* fragmentPath, 
			  const char* geometryPath = nullptr);
	void setLightPos(glm::vec3 lightPos) { _lightPos = lightPos; }
protected:
	glm::fvec3 _lightPos;
	glm::fvec3 _lightColor, _objColor;
	unsigned int _diffuse_tex_id, _specular_tex_id;

	void postInitial();
	void onDraw3D_CUBE();
};

#endif
