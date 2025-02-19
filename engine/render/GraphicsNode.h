#pragma once
#include <config.h>
#include <GL/glew.h>
#include <memory>
#include <cstring>
#include "core/mat4.h" // matrix 4x4 class for transformations 
#include "core/vec4.h"
#include "core/vec3.h"
#include "core/vec2.h"
#include "render/Camera.h"
#include "render/MeshResource.h"
#include "render/ShaderResource.h"
#include "render/WindowWrapper.h"
#include "render/TextureResource.h"
#include "render/PointLightSourceNode.h"
#include "render/DirectionalLight.h"



// test for github


using namespace std;

class GraphicsNode
{
public:
	// constrrctor and destructor. 
	GraphicsNode();
	GraphicsNode(shared_ptr<MeshResource> meshResource, shared_ptr<ShaderResource> shaderResource, std::shared_ptr<TextureResource> textureResource);
	~GraphicsNode();

	//Add get/set functions for all the resource types, or expose them as public members (your preference).


	void SetMeshResource(shared_ptr<MeshResource> mesh); 	// mesh geometry 

	shared_ptr<MeshResource> GetMeshResource() const; // retrive the meshresource
	
	void SetShaderResource(shared_ptr<ShaderResource> shader); // with shader progrma be used to render objects. 
	shared_ptr<ShaderResource> GetShaderResource() const; // retrive the shaderResource


	void SetTextureResource(shared_ptr<TextureResource> texture); // used applying on the objects. 
	shared_ptr<TextureResource> GetTextureResource() const; // retrive the TextureResource

	void SetTransform(const mat4& transform); // transformation matrix use to rotation, position and scaling. 
	const mat4& GetTransform() const; // retrive the current transformation. 

	void Rotate(float angle, const vec3& axis); // rotating the object around here is axis. 
	void Scale(const vec3& scalingFactors); // scaling the object vex(x,y,z) axis. 

	//Add a draw function that will bind the resource objects, apply the transform and finally render the object.
	void Draw(Camera& camera,  PointLightSourceNode& LightSource,  DirectionalLight& SunLight,  bool isUsingLight);

	mat4 transform;
private:

	// smart pointer to resources share between GraphicsNode and instance. 
	// mesh geometry, shader program and textrure
	std::shared_ptr<MeshResource> meshResource; 
	std::shared_ptr<ShaderResource> shaderResource;
	std::shared_ptr<TextureResource> textureResource;

	//transformation matrix for position, rotation and scaling.
	
};
