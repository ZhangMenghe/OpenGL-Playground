#include <GL/freeglut.h>
#include <iostream>
#include <WaterRender.h>
#include<glm/gtc/matrix_transform.hpp>
WaterRender * renderer;
bool gMouseLeftButton;
glm::vec2 gMouseCurrentPos, gMouseMovePos;

glm::mat4 rotx(float a) {
	float s = std::sin(a);
	float c = std::cos(a);
	return glm::mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, c, s, 0.0f,
		0.0f, -s, c, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
};
glm::mat4 roty(float a) {
	float s = std::sin(a);
	float c = std::cos(a);
	return glm::mat4(
		c, 0.0f, -s, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		s, 0.0f, c, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
};

void onViewChange(int width, int height) {
	float aspect = ((float)width) / height;

	// Calculate the projection matrix    
	float fovy = 45.0f;
	float near_plane = 0.01f;
	float far_plane = 1000.0f;

	renderer->setProjectionMatrix(glm::perspective(fovy, aspect, near_plane, far_plane));
	// Set the viewport to be the entire window
	glViewport(0, 0, width, height);
}
void onDrawFrame()
{
	renderer->RotateView(gMouseCurrentPos - gMouseMovePos);
	gMouseCurrentPos = gMouseMovePos;

	renderer->onDraw3D();
	glutSwapBuffers();
}
void onInitial() {
	renderer->onInitial();
}
void onDestroy() {
	renderer->onDestroy();
}
void processNormalKeys(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		exit(0);
		break;
	case 'w': case 'W':
		renderer->ZoomIn();
		break;
	case 's': case 'S':
		renderer->ZoomOut();
		break;
	default:
		break;
	}
}

void processMouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		gMouseLeftButton = (state == GLUT_DOWN) ? true : false;
		gMouseCurrentPos = glm::vec2(x, y);
		gMouseMovePos = gMouseCurrentPos;
	}
}

void processMouseActiveMotion(int x, int y) {
	if (gMouseLeftButton) {
		gMouseMovePos = glm::vec2(x, y);
	}
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(512, 512);
	glutCreateWindow("WINDOW NAME");
	renderer = new WaterRender("Shaders/water.vert", "Shaders/water.frag");
	glutReshapeFunc(onViewChange);

	glutDisplayFunc(onDrawFrame);
	/*glutIdleFunc(renderScene);*/
	
	glutKeyboardFunc(processNormalKeys);
	glutMouseFunc(processMouse);
	glutMotionFunc(processMouseActiveMotion);

	//glClearColor(0.3, 0.4, 0.6, 1.0);

	onInitial();

	glutMainLoop();

	// delete GL objects 
	onDestroy();

	return 0;
}
