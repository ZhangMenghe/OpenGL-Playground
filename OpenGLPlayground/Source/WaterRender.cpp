#include <GL/glew.h>
#include <string.h>
#include <WaterRender.h>
#include <GL/freeglut.h>

WaterRender::WaterRender(const char* vertexPath, const char* fragmentPath, const char* geometryPath)
	:TextureRender(vertexPath, fragmentPath, geometryPath){
}
void WaterRender::onInitial() {
	_vertice_num = (QUAD_GRID_SIZE + 1)*(QUAD_GRID_SIZE + 1);
	_indices_num = 6 * QUAD_GRID_SIZE * QUAD_GRID_SIZE;
	
	_vertices = new float[3 * _vertice_num];
	_uvs = new float[2 * _vertice_num];
	_indices = new GLuint[_indices_num];

	//Generate grid positions
	const float scale = 50.0f;
	const float delta = 2.0f / QUAD_GRID_SIZE;

	for (int y = 0; y <= QUAD_GRID_SIZE; y++) {
		int yPosition = y * (QUAD_GRID_SIZE + 1);
		for (int x = 0; x <= QUAD_GRID_SIZE; x++) {
			int idx = 3 * (yPosition + x), iduv = 2 * (yPosition + x);
			_vertices[idx] = (x*delta - 1.0f) * scale;
			_vertices[idx+1] = 0;
			_vertices[idx+2] = (y*delta - 1.0f) * scale;
			_uvs[iduv] = x * delta;
			_uvs[iduv+1] = y * delta;
		}
	}

	// Generate indices into vertex list
	for (int y = 0; y<QUAD_GRID_SIZE; y++) {
		int yPosition = y * QUAD_GRID_SIZE;
		for (int x = 0; x<QUAD_GRID_SIZE; x++) {
			int idx = 6 * (yPosition + x );
			// tri 0
			_indices[idx] = y * (QUAD_GRID_SIZE + 1) + x;    //bl  
			_indices[idx + 1] = (y + 1)*(QUAD_GRID_SIZE + 1) + x + 1;//tr
			_indices[idx + 2] = y * (QUAD_GRID_SIZE + 1) + x + 1;//br
																			  // tri 1
			_indices[idx + 3] = y * (QUAD_GRID_SIZE + 1) + x;    //bl
			_indices[idx + 4] = (y + 1)*(QUAD_GRID_SIZE + 1) + x;    //tl
			_indices[idx + 5] = (y + 1)*(QUAD_GRID_SIZE + 1) + x + 1;//tr
		}
	}
	_initialize_buffers_static();
	create2DTexture("Resources/waves.png");
	const char* filenames[6] = { "Resources/skybox/cloudyhills_posx.png", "Resources/skybox/cloudyhills_negx.png",
		"Resources/skybox/cloudyhills_posy.png", "Resources/skybox/cloudyhills_negy.png",
		"Resources/skybox/cloudyhills_posz.png", "Resources/skybox/cloudyhills_negz.png" };
	createCubeTexture(filenames);
}

void WaterRender::onDraw3D() {	
	TextureRender::onDraw3D();
	shaderHelper->use();
	shaderHelper->setFloat("uTime", glutGet(GLUT_ELAPSED_TIME) / 1000.0f);
}
