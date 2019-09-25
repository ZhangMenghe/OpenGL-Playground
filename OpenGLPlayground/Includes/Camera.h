#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera{
public:
	static Camera* ptr;
	static Camera* instance();
	bool FPS_MODE = true;
	// Camera Attributes
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Center;
	glm::vec3 Right;
	
	// Euler Angles
	float Yaw;
	float Pitch;
	// Camera options
	float MovementSpeed;
	float MouseSensitivity;
	float Fov;
	float screen_ratio = -1.0f;
	glm::mat4 ProjMat = glm::mat4(1.0f);
	//glm::mat4 ViewMat = glm::mat4(1.0f);
	
	// Constructor with vectors
	Camera();
	// Constructor with scalar values
	Camera(glm::vec3 pos, glm::vec3 center);

	void setPosition(glm::vec3 pos) { Position = pos; }
	void setCenter(glm::vec3 center) { Center = center; FPS_MODE = false;}
	glm::vec3 GetCameraPosition();
	// Returns the view matrix calculated using Euler Angles and the LookAt Matrix
	glm::mat4 GetViewMatrix();
	
	void setProjectionMatrix(int screen_width, int screen_height);
	glm::mat4 getProjectionMatrix();
	void getScreenShape(int& width, int& height) {
		width = _sw; height = _sh;
	}
	void getCameraProjectionPlane(float& near_plane, float & far_plane) { near_plane = NEAR_PLANE; far_plane = FAR_PLANE; }
	// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
	void Move_Camera(Camera_Movement direction, float deltaTime);
	// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void Rotate_Camera(float xoffset, float yoffset, bool constrainPitch = true);

	// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void Zoom_Camera(int dir);
private:
	// Default camera values
	const float YAW = -90.0f;
	const float PITCH = 0.0f;
	const float SPEED = .05f;
	const float SENSITIVITY = 0.005f;
	const float ZOOM_SENSITIVE = 0.1f;

	const float NEAR_PLANE = 0.1f;
	const float FAR_PLANE = 20.0f;
	const float FOV = 45.0f;
	const glm::vec3 WORLD_FRONT = glm::vec3(0, 0, -1);
	const glm::vec3 WorldUp = glm::vec3(0,1,0);
	glm::vec3 LOOK_CENTER;

	int _sw, _sh;
	float _sw_inv, _sh_inv;

	// Calculates the front vector from the Camera's (updated) Euler Angles
	void updateCameraVectors();
};
#endif