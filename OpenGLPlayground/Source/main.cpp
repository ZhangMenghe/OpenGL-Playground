#include <GL/freeglut.h>
#include <iostream>
#include <PhongCube.h>
#include <glm/gtc/matrix_transform.hpp>

extern void SpecialKey(int key, int x, int y);
extern void KeyBoard(unsigned char key, int x, int y);
extern void MouseControl(int button, int state, int x, int y);
extern void MouseMotion(int x, int y);
extern void MouseWheel(int, int, int, int);

PhongCube * renderer;
SimpleCube* lamp;

glm::fvec3 lightPos = glm::fvec3(1.2, 1.0, 2.0);
glm::mat4 lampModel = glm::scale(glm::mat4(1.0f), glm::fvec3(0.3f));
float deltaTime = .0f, lastFrame = .0f;
extern float FOV;
extern const float NEAR_PLANE, FAR_PLANE;

void onViewChange(int width, int height) {
	renderer->setProjectionMatrix(glm::perspective(FOV, ((float)width) / height,
												   NEAR_PLANE, FAR_PLANE));
	lamp->setProjectionMatrix(glm::perspective(FOV, ((float)width) / height,
		NEAR_PLANE, FAR_PLANE));

	// Set the viewport to be the entire window
	glViewport(0, 0, width, height);
}
void onDrawFrame() {
	deltaTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f - lastFrame;
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	renderer->onDraw3D();
	lamp->onDraw3D();
	//glutPostRedisplay();
	glutSwapBuffers();
}
void updateLight() {
	lampModel = glm::translate(lampModel, lightPos);
	lamp->setModelMatrix(lampModel);

	renderer->setLightPos(lightPos);
}
void onInitial() {
	renderer->onInitial();
	lamp->onInitial();
	updateLight();
}
void onDestroy() {
	renderer->onDestroy();
	lamp->onDestroy();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(512, 512);
	glutCreateWindow("WINDOW NAME");
	//renderer = new WaterRender("Shaders/water.vert", "Shaders/water.frag");
	renderer = new PhongCube("Shaders/compLight.vert",
							  "Shaders/compLight.frag");
	lamp = new SimpleCube("Shaders/cube.vert", "Shaders/cube.frag");

	glutReshapeFunc(onViewChange);

	glutDisplayFunc(onDrawFrame);
	glutIdleFunc(onDrawFrame);
	glutSpecialFunc(SpecialKey);
	glutKeyboardFunc(KeyBoard);
	glutMouseFunc(MouseControl);
	glutMotionFunc(MouseMotion);
	glutMouseWheelFunc(MouseWheel);

	onInitial();

	glutMainLoop();

	// delete GL objects 
	onDestroy();

	return 0;
}
