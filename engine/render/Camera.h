#pragma once
#include <config.h>
#include <GL/glew.h>
#include <string>
#include <iostream>
#include "core/mat4.h"
#include "core/vec3.h"

class Camera
{
public:
	Camera(vec3 position, vec3 target, vec3 up); 
	void update(); 
	void setAspectRatio(float ratio); 
	mat4 getViewMatrix(); 

	


};

