#pragma once
#include <PhongCube.h>
#include <GL/freeglut.h>
#include <glm/gtc/matrix_transform.hpp>
#include <Camera.h>

glm::fvec2 Mouse_old = glm::fvec2(.0), Mouse_current = glm::fvec2(.0);

extern float deltaTime;

void SpecialKey(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_RIGHT:
		Camera::instance()->Move_Camera(RIGHT, deltaTime);
		break;
	case GLUT_KEY_LEFT:
		Camera::instance()->Move_Camera(LEFT, deltaTime);
		break;
	case GLUT_KEY_UP:
		Camera::instance()->Move_Camera(FORWARD, deltaTime);
		break;
	case GLUT_KEY_DOWN:
		Camera::instance()->Move_Camera(BACKWARD, deltaTime);
		break;
	default:
		break;
	}
}

void KeyBoard(unsigned char key, int x, int y) {

}

void MouseControl(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) Mouse_old = glm::fvec2(x, y);
		if (state == GLUT_UP) {
		}
		break;
	default:
		break;
	}
	//glutPostRedisplay();
}

void MouseMotion(int x, int y) {
	Camera::instance()->Rotate_Camera(x - Mouse_old.x, Mouse_old.y - y);
	Mouse_old = glm::fvec2(x, y);
}

void MouseWheel(int button, int dir, int xoffset , int yoffset) {
	Camera::instance()->Zoom_Camera(dir);
}