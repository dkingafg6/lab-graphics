#pragma once
#include "config.h"
#include "render/Camera.h"
#include <cmath>



using namespace std; 

// constructor 
Camera::Camera()
{

}

Camera::Camera(const vec3& pos, const vec3& target, const vec3& up,float fov, float aspect, float nearPlane, float farPlane) : position(pos), target(target), up(up), fov(fov), aspect(aspect), nearPlane(nearPlane), farPlane(farPlane),
yaw(-90.0f), pitch(0.0f), sensitivity(0.1f), lastX(400), lastY(300), firstMouse(true)
{/*
	position = vec3(0.0f, 0.0f, 3.0f);
	target = vec3(0.0f, 0.0f, 0.0f); 
	up = vec3(0.0f, 1.0f, 0.0f); 
	fieldOfView = 45.0f; 
	apsectRatio = 1.0f; 
	nearClip = 0.1f; 
	farClip = 100.0f; */

	updateTarget();
}


// Calculate the perspective matrix:
mat4 Camera::getPerspectiveMatrix() const
{
	// convert fov t radians to calculate tangent. 
	// since using asing(1.0) will return the value for pi/2. therefore, to get the value of pi is (pi = (2*asin(1.0))
	float tanHalfFov = tan(fov * 0.5f * (2 * asin(1.0) / 180.0f));

	mat4 perspective(0.0f);
	// scaling x-z
	perspective[0][0] = 1.0f / (aspect * tanHalfFov);
	perspective[1][1] = 1.0f / tanHalfFov;
	perspective[2][2] = -(farPlane + nearPlane) / (farPlane - nearPlane);
	// projection t 2D plane 
	perspective[2][3] = -1.0f;
	// depth translation 
	perspective[3][2] = -(2.0f * farPlane * nearPlane) / (farPlane - nearPlane);

	return perspective;

}


// calculate the combined projection = perspective * view.
mat4 Camera::getProjectionMatrix() const
{
	return getPerspectiveMatrix() * getViewMatrix();
}


// move the camera ( translate in world space) 
void Camera::move(const vec3& delta)
{
	position += delta;
	target += delta;
}

// rotate the camera(yaw and pitch)
void Camera::setFOV(float yaw, float pitch)
{
	this->yaw = yaw;
	this->pitch = pitch;
	updateTarget();

}


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


// setters for fov aspect ratio, and clipping plans. 
void Camera::setClippingPlanes(float newNear, float newFar)
{
	nearPlane = newNear; 
	farPlane = newFar; 
}



void Camera::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;

	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reverses since y- coordinate go from bottom to top. 
	lastX = xpos;
	lastY = ypos;

	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// pitch 
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	// update the target direction after adjustint yaw and pitch
	updateTarget();
}

// process Keyboard and mouse input;
void Camera::processInput(GLFWwindow* window, Camera& camera)
{
	const float cameraSpeed = 0.05f; // adjust accordingly for movement speed
	vec3 forward = normalize(camera.target - camera.position); // camera direction vector
	vec3 right = normalize(cross(camera.up, forward)); // perpendicular to up and forward, 

	// move forward
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.move(forward * cameraSpeed);

	}
	// move backward
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.move(-forward * cameraSpeed);

	}
	// move left
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.move(-right * cameraSpeed);

	}
	// move right 
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.move(right * cameraSpeed);
	}
	 // update yaw and pitch 
	camera.setFOV(camera.yaw, camera.pitch); 
	
}

// setters for fov aspect ratio, and clipping plans. 
vec3 Camera::rotateX(const vec3& v, float angle) const
{
	float rad = angle * (2 * asin(1.0) / 180.0f);
	float cosAngle = cos(rad);
	float sinAngle = sin(rad);
	return vec3(v.x, v.y * cosAngle - v.z * sinAngle, v.y * sinAngle + v.z * cosAngle);
}

// setters for fov aspect ratio, and clipping plans. 
vec3 Camera::rotateY(const vec3& v, float angle) const
{
	float rad = angle * (2 * asin(1.0) / 180.0f);
	float cosAngle = cos(rad);
	float sinAngle = sin(rad);
	return vec3(v.z * sinAngle + v.x * cosAngle, v.y, v.z * cosAngle - v.x * sinAngle);

}

void Camera::updateTarget()
{
	// caculate direction based on (pitch and yaw)
	vec3 direction;
	direction.x = cos(radians(yaw)) * cos(radians(pitch));
	direction.y = sin(radians(pitch));
	direction.z = sin(radians(yaw)) * cos(radians(pitch));

	// normilize direction vector
	target = normalize(direction);
}





mat4 Camera::getViewMatrix() const
{
	vec3 zaxis = normalize(position - target); // forward
	vec3 xaxis = normalize(cross(up, zaxis)); // right
	vec3 yaxis = cross(zaxis, xaxis);         //up


	// construction for veiw matrix
	mat4 view;
	view[0] = vec4(xaxis.x, yaxis.x, zaxis.x, 0.0f);
	view[1] = vec4(xaxis.y, yaxis.y, zaxis.y, 0.0f);
	view[2] = vec4(xaxis.z, yaxis.z, zaxis.z, 0.0f);
	view[3] = vec4(-dot(xaxis, position), -dot(yaxis, position), -dot(zaxis, position), 1.0f);

	return view;
}
	


	

