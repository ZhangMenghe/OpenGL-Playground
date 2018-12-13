#include <GL/freeglut.h>
#include <iostream>
#include <SimpleQuad.h>
SimpleQuad * renderer;

void displayMe()
{
	renderer->onDraw();
	glutSwapBuffers();
}
void initRender() {
	renderer->onInitial();
}
void cleanUp() {
	renderer->onDestroy();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(512, 512);
	glutCreateWindow("WINDOW NAME");
	renderer = new SimpleQuad("Shaders/texture.vert", "Shaders/texture.frag");
	

	glutDisplayFunc(displayMe);
	/*glutIdleFunc(renderScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(processNormalKeys);
	glutMouseFunc(processMouse);
	glutMotionFunc(processMouseActiveMotion);*/

	//glClearColor(0.3, 0.4, 0.6, 1.0);

	initRender();

	glutMainLoop();

	// delete GL objects 
	cleanUp();

	return 0;
}
