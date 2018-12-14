#include <GL/freeglut.h>
#include <iostream>
#include <WaterRender.h>
#include <glm/gtc/matrix_transform.hpp>

extern void SpecialKey(int key, int x, int y);
extern void KeyBoard(unsigned char key, int x, int y);
extern void MouseControl(int button, int state, int x, int y);
extern void MouseMotion(int x, int y);

WaterRender * renderer;
float deltaTime = .0f, lastFrame=.0f;

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
void onDrawFrame() {
	deltaTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f - lastFrame;

	renderer->onDraw3D();
	//glutPostRedisplay();
	glutSwapBuffers();
}
void onInitial() {
	renderer->onInitial();
}
void onDestroy() {
	renderer->onDestroy();
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
	glutIdleFunc(onDrawFrame);
	glutSpecialFunc(SpecialKey);
	glutKeyboardFunc(KeyBoard);
	glutMouseFunc(MouseControl);
	glutMotionFunc(MouseMotion);

	onInitial();

	glutMainLoop();

	// delete GL objects 
	onDestroy();

	return 0;
}
