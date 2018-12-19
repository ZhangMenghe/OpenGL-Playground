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
	// Camera Attributes
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
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
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

	glm::vec3 GetCameraPosition();
	// Returns the view matrix calculated using Euler Angles and the LookAt Matrix
	glm::mat4 GetViewMatrix();
	
	void setProjectionMatrix(int screen_width, int screen_height);
	glm::mat4 getProjectionMatrix();
	// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
	void Move_Camera(Camera_Movement direction, float deltaTime);
	// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void Rotate_Camera(float xoffset, float yoffset, bool constrainPitch = true);

	// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void Zoom_Camera(int dir);
private:
	// Default camera values
	const  float YAW = -90.0f;
	const float PITCH = 0.0f;
	const float SPEED = .05f;
	const float SENSITIVITY = 0.1f;
	const float ZOOM_SENSITIVE = 0.1f;

	const float NEAR_PLANE = 0.01f;
	const float FAR_PLANE = 1000.0f;
	const float FOV = 45.0f;

	// Calculates the front vector from the Camera's (updated) Euler Angles
	void updateCameraVectors();
};
#endif