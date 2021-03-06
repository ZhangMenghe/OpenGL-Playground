#include <Config.h>
#include <PhongCube.h>
#include <Camera.h>
#include <glm/gtc/matrix_transform.hpp>
#include <Shadow.h>

extern void SpecialKey(int key, int x, int y);
extern void KeyBoard(unsigned char key, int x, int y);
extern void MouseControl(int button, int state, int x, int y);
extern void MouseMotion(int x, int y);
extern void MouseWheel(int, int, int, int);

//PhongCube * renderer;
//SimpleCube* lamp;
ShadowRender* renderer;

glm::fvec3 lightPos = glm::fvec3(1.2, 2.5, 2.0);
glm::mat4 lampModel = glm::scale(glm::mat4(1.0f), glm::fvec3(0.3f));
float deltaTime = .0f, lastFrame = .0f;


void onViewChange(int width, int height) {
	Camera::instance()->setProjectionMatrix(width, height);
	glViewport(0, 0, width, height);
}
void onDrawFrame() {
	deltaTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f - lastFrame;
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	renderer->onDraw3D();
	//lamp->onDraw3D();
	glutPostRedisplay();
	glutSwapBuffers();
}
void updateLight() {
	//lampModel = glm::translate(lampModel, lightPos);
	//lamp->setModelMatrix(lampModel);

	//renderer->setLightPos(lightPos);
}
void onInitial() {
	//Camera(glm::vec3(.0f, 0.5f, 7.0f), LOOKAT_CENTER);
	Camera::instance()->setPosition(glm::vec3(.2f, 0.5f, 10.0f));
	//Camera::instance()->setCenter(LOOKAT_CENTER);
	renderer->onInitial();
	//lamp->onInitial();
	//updateLight();
}
void onDestroy() {
	renderer->onDestroy();
	//lamp->onDestroy();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	glutCreateWindow("WINDOW NAME");
	//renderer = new WaterRender("Shaders/water.vert", "Shaders/water.frag");
	//renderer = new PhongCube("Shaders/compLight.vert",
	//						  "Shaders/compLight.frag");
	//lamp = new SimpleCube("Shaders/cube.vert", "Shaders/cube.frag");

	GLenum err = glewInit();
	// Test for OpenGL 3
	if (GLEW_VERSION_3_0) {
		printf("GL version 3 supported \n");
	}

	renderer = new ShadowRender;
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
