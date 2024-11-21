#pragma once
#include <config.h>
#include "GraphicsNode.h"
#include <render/Camera.h>

using namespace std; 
// test 


GraphicsNode::GraphicsNode()
{
}

GraphicsNode::GraphicsNode(shared_ptr<MeshResource> meshResource, shared_ptr<ShaderResource> shaderResource, std::shared_ptr<TextureResource> textureResource)
{
	this->SetMeshResource(meshResource);
	this->SetShaderResource(shaderResource);
	this->SetTextureResource(textureResource);
}

GraphicsNode::~GraphicsNode()
{
}
// set and assign the meshResouce to the node. 
void GraphicsNode::SetMeshResource(shared_ptr<MeshResource> mesh)  
{
	this->meshResource = mesh; 
}

// Retrieves and return the meshrescorce 
shared_ptr<MeshResource> GraphicsNode::GetMeshResource() const
{
	return this->meshResource;
}

// set and assign the shederResouce to the node. 
void GraphicsNode::SetShaderResource(shared_ptr<ShaderResource> shader)
{
	this->shaderResource = shader; 
}

// Retrieves for and return to the shaderrescorce to this node. 
shared_ptr<ShaderResource> GraphicsNode::GetShaderResource() const
{
	return this->shaderResource;
}

// sets ans assign the texturResurces for this node. 
void GraphicsNode::SetTextureResource(shared_ptr<TextureResource> texture)
{
	this->textureResource = texture; 
}

// Retrieves for and return to the texturerescorce to this node. 
shared_ptr<TextureResource> GraphicsNode::GetTextureResource() const
{
	return this->textureResource;
}

// sets the trans..matrix for this node. 
void GraphicsNode::SetTransform(const mat4& transform)
{
	this->transform = transform; 
}

// 
const mat4& GraphicsNode::GetTransform() const
{
	return this->transform; 
	
}
// testing 
void GraphicsNode::Translate(const vec3& translation)
{
	mat4 translationMatrix = mat4::translation(translation);
	transform = translationMatrix * transform; // apply the translation. 
}
	

void GraphicsNode::Rotate(float angle, const vec3& axis)
{
	mat4 rotationMatrix = mat4::rotationaxis(axis, angle);
	transform = rotationMatrix * transform; // apply the rotation. 
}

void GraphicsNode::Scale(const vec3& scalingFactors)
{
	mat4  scalingMatrix = mat4::scaling(scalingFactors);
	transform = scalingMatrix * transform; // apply the scaling .

}

void GraphicsNode::Draw(Camera& camera)
{ 
	shaderResource->UseProgram();
	shaderResource->SetUniformMatrix4fv("model", this->GetTransform());
	shaderResource->SetUniformMatrix4fv("view", camera.getViewMatrix());
	shaderResource->SetUniformMatrix4fv("projection", camera.getPerspectiveMatrix());

	textureResource->Bind();


	meshResource->BindVBO();
	meshResource->BindIBO();// update the camera based on mouse mouvement. 
	glDrawElements(GL_TRIANGLES,meshResource->indexSize, GL_UNSIGNED_INT, (void*)NULL);// render and draw the cube.
	glBindVertexArray(0);

}
