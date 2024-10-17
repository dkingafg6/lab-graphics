#pragma once
#include <config.h>
#include <GL/glew.h>
#include <cstring>
#include "core/mat4.h"
#include "render/MeshResource.h"
#include "render/ShaderResource.h"
#include "render/WindowWrapper.h"
#include "render/TextureResource.h"

using namespace std;

class GraphicsNode
{
public:
	GraphicsNode();
	~GraphicsNode();
	//Add get/set functions for all the resource types, or expose them as public members (your preference).
	void SetMeshResource(shared_ptr<MeshResource> mesh); 
	shared_ptr<MeshResource> GetMeshResource() const; 
	
	void SetShaderResource(shared_ptr<ShaderResource> shader);
	shared_ptr<ShaderResource> GetShaderResource() const; 


	void SetTextureResource(shared_ptr<TextureResource> texture); 
	shared_ptr<TextureResource> GetTextureResource() const; 

	void SetTransform(const mat4& transform);
	const mat4& GetTransform() const; 

	void Translate(const vec3& translation); 
	void Rotate(float angle, const vec3& axis); 
	void Scale(const vec3& scalingFactors); 

	//Add a draw function that will bind the resource objects, apply the transform and finally render the object.
	void Draw(); 


private:

	// smart pointer to resources share between GraphicsNode and instance. 
	std::shared_ptr<MeshResource> meshResource; 
	std::shared_ptr<ShaderResource> shaerResource;
	std::shared_ptr<TextureResource> textureResource;

	//transformation matrix. 
	mat4 transform; 
};
