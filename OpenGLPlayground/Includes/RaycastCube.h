#ifndef RAYCAST_CUBE_H
#define RAYCAST_CUBE_H

#include <SimpleCube.h>

class RaycastCube : public SimpleCube{
public:
	RaycastCube(const char* vertexPath, const char* fragmentPath,
		const char* geometryPath = nullptr);
	void onInitial();
protected:
	void postInitial();

	void preDraw3D_CUBE();
	void onDraw3D_CUBE();
	void postDraw3D_CUBE();
private:
	// File has only image data. The dimension of the data should be known.
	unsigned int m_uImageCount = 109;
	unsigned int m_uImageWidth = 256;
	unsigned int m_uImageHeight = 256;
	unsigned int m_tex_3d_id, m_tex_trans_id;

};

#endif
