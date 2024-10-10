#pragma once
#include "config.h"
#include "render/Camera.h"
#include <cmath>



using namespace std; 

// constructor 


Camera::Camera() 
	: position(0.0f, 0.0f, 3.0f), target(0.0f, 0.0f, 0.0f), up(0.0f, 1.0f, 0.0f),
	fov(45.0f), aspect(1.0f), nearPlane(0.1f), farPlane(100.0f), firstMouse(true)
{
	//ASD
}

Camera::Camera(int width, int height, vec3 position) : width(width), height(height), position(position)
{
	firstMouse = true; 
	lastX = width / 2.0f;
	lastY = width / 2.0f; 
	aspect = static_cast<float>(width) / height; 
	updateTarget(); 

}

Camera::Camera(const vec3& pos, const vec3& target, const vec3& up,float fov, float aspect, float nearPlane, float farPlane) 
	: position(pos), target(target), up(up), fov(fov), aspect(aspect), nearPlane(nearPlane), farPlane(farPlane)
	
{

	updateTarget();
}

// update target direction based on yaw and pitch
void Camera::updateTarget()
{
	// calculate direction based on (pitch and yaw)
	vec3 direction;
	direction.x = cos(radians(yaw)) * cos(radians(pitch));
	direction.y = sin(radians(pitch));
	direction.z = sin(radians(yaw)) * cos(radians(pitch));

	// normalize direction vector
	target = normalize(direction);
}

// view = lookAt use lookAt function. 
mat4 Camera::getViewMatrix() const
{

	return lookat(position, position + target, up);
}


// Calculate the perspective matrix:
mat4 Camera::getPerspectiveMatrix() const
{
	return perspective(fov, aspect, nearPlane,farPlane);
}


// calculate the combined projection = perspective * view.
mat4 Camera::getProjectionMatrix() const
{
	return getPerspectiveMatrix() * getViewMatrix();
}

// move the camera(translate in world space)
void Camera::move(const vec3 & delta)
{
	position += delta;
	//target += delta;
}

//void Camera::setFOV(float yaw, float pitch)
//{
//
//}

// send camera's matrix to shader. 
void Camera::updateCameraMatrix(float FOVdeg, GLuint shaderProgram, const char* uniform)
{
	// camera matrix (projection * view )
	mat4 cameraMatrix = getProjectionMatrix(); 

	// get location from uniform in the shader porgram. 
	GLuint uniformLocatio = glGetUniformLocation(shaderProgram, uniform); 

	// set matrix data to the shader using glUniformMatrix4fv
	glUniformMatrix4fv(uniformLocatio, 1, GL_FALSE, &cameraMatrix[0][0]); 
	
}

//void Camera::setFOV(float yaw, float pitch)
//{
//
//}




//
//void Camera::setFOV(float yaw, float pitch)
//{
//}

// setters for fov aspect ratio, and clipping plans. 
void Camera::setFOV(float newFOV)
{
	fov = newFOV;
}


// setters for fov aspect ratio, and clipping plans. 
void Camera::setAspectRatio(float newAspect)
{
	aspect = newAspect;
}
void Camera::setClippingPlanes(float newNear, float newFar)
{
	nearPlane = newNear;
	farPlane = newFar;
}

/*oid Camera::SetKeyPressFunction(const std::function<void(int32, int32, int32, int32)>& func)
{
}

void Camera::SetMousePressFunction(const std::function<void(int32, int32, int32)>& func)
{
}

void Camera::SetMouseMoveFunction(const std::function<void(float64, float64)>& func)
{
	Window* window = (Window*)glfwGetWindowUserPointer(win); 
}*/


void Camera::mouse_callback(float64 xpos, float64 ypos)
{

	static double lastX = xpos; 
	static double lastY = ypos; 

	// calculate the offsets based on movement of the mouse.  
	double xoffset = xpos - lastX;
	double yoffset = ypos - lastY; // reverses since y- coordinate go from bottom to top. 

	lastX = xpos;
	lastY = ypos;

	// adjusting this how sensitivity has the mouse with changing. 
	const float sensitivity  = 0.05f; 

	// the sensitivity. 
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	// fix the direction of the camera in (x and y ) coordinate to move with mouse direction. 
	xoffset = xoffset; 
	yoffset = -yoffset; 

	// update 
	yaw += xoffset;
	pitch += yoffset;

	// this function help the camera to not flipping upside down. 
	clamPicth(); 


	// update the target direction after adjusting yaw and pitch
	updateTarget();
}

void Camera::clamPicth()
{
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

}

//window.SetMouseMoveFunctin([this](float64 z, float y) 
//	{
//
//	}
// process Keyboard and mouse input;
void Camera::processInput(GLFWwindow* window)
{
	const float cameraSpeed = speed; // adjust accordingly for movement speed
	vec3 forward = normalize(target - position); // camera direction vector
	vec3 right = normalize(cross(up, forward)); // perpendicular to up and forward, 
	vec3 upDirection = normalize(up);          // normalize up vector for vertical movement. 

	// move forward
	if (glfwGetKey(window,  GLFW_KEY_W) == GLFW_PRESS)
	{
		move(forward * cameraSpeed);

	}
	// move backward
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		move(-forward * cameraSpeed);

	}
	// move right
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		move(right * cameraSpeed);

	}
	// move left
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		move(-right * cameraSpeed);
	}
	// move down
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		move(-upDirection * cameraSpeed);
	}
	// move up
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		move(upDirection * cameraSpeed);
	}
	// update camera target after moving
	updateTarget(); 
	
}





	

