#include <Camera.h>
Camera* Camera::ptr = NULL;
Camera * Camera::instance() { 
	if (!ptr) ptr = new Camera();
return ptr;}

Camera::Camera(){
	Position = glm::vec3(0.0f, 0.0f, 3.0f);

	Front = WORLD_FRONT;
	Center = Position + Front;
	Yaw = YAW;
	Pitch = PITCH;
	MovementSpeed = SPEED;
	MouseSensitivity = SENSITIVITY;
	Fov = FOV;
	updateCameraVectors();
}
	// Constructor with scalar values
Camera::Camera(glm::vec3 pos, glm::vec3 center){
		Position = pos;
		Center = center;
		FPS_MODE = false;
		Front = WORLD_FRONT;
		Yaw = YAW;
		Pitch = PITCH;
		MovementSpeed = SPEED;
		MouseSensitivity = SENSITIVITY;
		Fov = FOV;
		updateCameraVectors();
		ptr = this;
	}
	glm::vec3 Camera::GetCameraPosition() { return Position; }
	// Returns the view matrix calculated using Euler Angles and the LookAt Matrix
	glm::mat4 Camera::GetViewMatrix() {
		return glm::lookAt(Position, Center, Up);
	}

	void Camera::setProjectionMatrix(int screen_width, int screen_height) {
		_sw = screen_width; _sh = screen_height;
		_sw_inv = 1.0f / _sw; _sh_inv = 1.0f / _sh;
		screen_ratio = ((float)screen_width) / screen_height;
		ProjMat = glm::perspective(FOV, screen_ratio, NEAR_PLANE, FAR_PLANE);
	}
	glm::mat4 Camera::getProjectionMatrix() {return ProjMat;}
	
	// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
	void Camera::Move_Camera(Camera_Movement direction, float deltaTime){
		float velocity = MovementSpeed * deltaTime;
		if (direction == FORWARD)
			Position += Front * velocity;
		if (direction == BACKWARD)
			Position -= Front * velocity;
		if (direction == LEFT)
			Position -= Right * velocity;
		if (direction == RIGHT)
			Position += Right * velocity;
		if(FPS_MODE)
			Center = Position + Front;
	}

	// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void Camera::Rotate_Camera(float xoffset, float yoffset, bool constrainPitch){
		glm::vec3 rotate_axis;
		float offset;
		if (fabs(xoffset* _sw_inv) > fabs(yoffset*_sh_inv)) {
			offset = xoffset * MouseSensitivity;
			rotate_axis = glm::vec3(0, 1, 0);
			Yaw += xoffset;
		}
		else {
			offset = -yoffset * MouseSensitivity;
			rotate_axis = glm::vec3(1,0, 0);
			Pitch += yoffset;
		}
		glm::mat4 modelMat = glm::mat4(1.0);
		//ROTATE CAMERA AROUND ITSELF
		modelMat = glm::rotate(modelMat, offset, rotate_axis);

		Front = glm::vec3(modelMat * glm::vec4(Front,1.0));
		// Also re-calculate the Right and Up vector
		Right = glm::vec3(glm::cross(Front, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		Up = glm::normalize(glm::cross(Right, Front));
		if (FPS_MODE)
			Center = Position + Front;
	}

	// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void Camera::Zoom_Camera(int dir){
		if (dir > 0) {
			//zoom in
			Fov = (Fov > 1.0F) ? Fov -= ZOOM_SENSITIVE : Fov;
			ProjMat = glm::perspective(Fov, screen_ratio, NEAR_PLANE, FAR_PLANE);
		}
		else {
			//zoom out
			Fov = (Fov < 45.0f) ? Fov += ZOOM_SENSITIVE : Fov;
			ProjMat = glm::perspective(Fov, screen_ratio, NEAR_PLANE, FAR_PLANE);
		}
	}


	// Calculates the front vector from the Camera's (updated) Euler Angles
	void Camera::updateCameraVectors(){
		// Calculate the new Front vector
		glm::vec3 front;
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		Front = glm::normalize(front);
		// Also re-calculate the Right and Up vector
		Right = glm::normalize(glm::cross(Front, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		Up = glm::normalize(glm::cross(Right, Front));
	}

