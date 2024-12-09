#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include "core/mat4.h"
#include "core/vec4.h"
#include "core/vec3.h"
#include "core/vec2.h"

#include "core/util.h"
#include "render/window.h"

#include "math.h"

class DirectionalLight
{
public:
	// direction, color and intensity of the ligh 
	vec3 direction; 
	vec3 color; 
	float intensity; 

	DirectionalLight(const vec3& direc, const vec3& col, float intens); 
		
	~DirectionalLight();

	void Apply_BPH_shader(GLuint shaderProgram);

private:

};

