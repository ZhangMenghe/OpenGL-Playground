#pragma once
#include <PhongCube.h>
#include <GL/freeglut.h>
#include <glm/gtc/matrix_transform.hpp>

extern PhongCube * renderer;
extern SimpleCube * lamp;

glm::fvec2 Mouse_old = glm::fvec2(.0), Mouse_current = glm::fvec2(.0);
float yaw = -90.0f, pitch = .0f;
const float MOVE_SPEED = .05f;
const float ROTATE_SENSITIVE = 0.1f;
const float ZOOM_SENSITIVE = 0.1f;

// Calculate the projection matrix    
float FOV = 45.0f;
extern const float NEAR_PLANE = 0.01f;
extern const float FAR_PLANE = 1000.0f;

const glm::fvec3 UP = glm::fvec3(.0, 1.0f, .0);
glm::fvec3 FRONT = glm::fvec3(.0, .0, -1.0);

extern float deltaTime;

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
		lamp->MoveCamera(m_translate);
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
	glm::fvec2 delta = glm::fvec2(x-Mouse_old.x, Mouse_old.y-y) * ROTATE_SENSITIVE;
	Mouse_old = glm::fvec2(x, y);
	yaw += delta.x; pitch += delta.y;
	pitch = (pitch > 89.0f) ? 89.0f : pitch;
	pitch = (pitch < -89.0f) ? -89.0f : pitch;
	
	FRONT.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	FRONT.y = sin(glm::radians(pitch));
	FRONT.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	FRONT = glm::normalize(FRONT);
	renderer->RotateCamera(FRONT);
	lamp->RotateCamera(FRONT);
	//glutPostRedisplay();
}
void MouseWheel(int button, int dir, int xoffset , int yoffset) {
	if (dir > 0) {
		//zoom in
		FOV = (FOV > 1.0F) ? FOV -= ZOOM_SENSITIVE : FOV;
		renderer->setProjectionMatrix(glm::perspective(FOV, (float)glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT),
			NEAR_PLANE, FAR_PLANE));
		lamp->setProjectionMatrix(glm::perspective(FOV, (float)glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT),
			NEAR_PLANE, FAR_PLANE));
	}
	else {
		//zoom out
		FOV = (FOV < 45.0f) ? FOV += ZOOM_SENSITIVE : FOV;
		renderer->setProjectionMatrix(glm::perspective(FOV, (float)glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT),
			NEAR_PLANE, FAR_PLANE));
		lamp->setProjectionMatrix(glm::perspective(FOV, (float)glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT),
			NEAR_PLANE, FAR_PLANE));
	}
}