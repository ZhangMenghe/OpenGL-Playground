#pragma once
#include <WaterRender.h>
#include <GL/freeglut.h>

extern WaterRender * renderer;
//extern SimpleCube * renderer;
extern float deltaTime;
const static float MOVE_SPEED = .2f;
const static float ROTATE_SENSITIVE = 1.0f;
const static glm::fvec3 FRONT = glm::fvec3(.0, .0, -1.0);
const static glm::fvec3 UP = glm::fvec3(.0, 1.0, .0);

glm::fvec2 Mouse_old = glm::fvec2(.0), Mouse_current = glm::fvec2(.0);

void SpecialKey(int key, int x, int y) {
	glm::fvec3 m_translate;
	bool bMove = false;
	float cameraSpeed = MOVE_SPEED * deltaTime;
	switch (key){
	case GLUT_KEY_RIGHT:
		m_translate = glm::normalize(glm::cross(FRONT, UP)) * cameraSpeed;
		bMove = true;
		break;
	case GLUT_KEY_LEFT:
		m_translate = -glm::normalize(glm::cross(FRONT, UP)) * cameraSpeed;
		bMove = true;
		break;
	case GLUT_KEY_UP:
		m_translate = cameraSpeed * FRONT;
		bMove = true;
		break;
	case GLUT_KEY_DOWN:
		m_translate = -cameraSpeed * FRONT;
		bMove = true;
		break;
	default:
		break;
	}
	if (bMove) {
		renderer->MoveCamera(m_translate);
		//glutPostRedisplay();
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
	glm::fvec2 delta = glm::fvec2(x-Mouse_old.x, y-Mouse_old.y) * ROTATE_SENSITIVE;
	Mouse_old = glm::fvec2(x, y);
	renderer->RotateCamera(delta);
	//glutPostRedisplay();
}