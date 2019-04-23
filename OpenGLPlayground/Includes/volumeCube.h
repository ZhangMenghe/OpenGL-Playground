#ifndef VOLUME_CUBE_H
#define VOLUME_CUBE_H
#include <SimpleCube.h>

class VolumeCube : public SimpleCube
{
public:
	VolumeCube(const char* vertexPath, const char* fragmentPath,
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

	GLuint* m_puTextureIDs;
	GLuint* m_VAOs;

};

#endif
