#pragma once
#include <config.h>
#include <GL/glew.h>
#include <memory>
#include <cstring>
#include "core/mat4.h" // matrix 4x4 class for transformations 
#include "core/vec4.h"
#include "core/vec3.h"
#include "core/vec2.h"
#include "render/MeshResource.h"
#include "render/ShaderResource.h"
#include "render/WindowWrapper.h"
#include "render/TextureResource.h" // some of include just for testint here.

using namespace std; 

class PointLightSourceNode 
{
public: 
	vec3 position; // pos for light in world space. 
	vec3 color; // color for the light. 
	float intensity;  // intencity of the light. 

	PointLight(const vec3& pos, const vec3& col, float intens); 
	void position(); 
	



private: 



};
