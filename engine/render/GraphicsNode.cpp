#pragma once
#include <config.h>
#include "GraphicsNode.h"

using namespace std; 


GraphicsNode::GraphicsNode()
{
}

GraphicsNode::~GraphicsNode()
{
}

void GraphicsNode::SetMeshResource(shared_ptr<MeshResource> mesh)
{
	this->meshResource = mesh; 
}

shared_ptr<MeshResource> GraphicsNode::GetMeshResource() const
{
	return this->meshResource;
}

void GraphicsNode::SetShaderResource(shared_ptr<ShaderRsource> shader)
{
	this->shaerResource = shader; 
}

shared_ptr<ShaderRsource> GraphicsNode::GetShaderResource() const
{
	return this->shaerResource;
}

void GraphicsNode::SetTextureResource(shared_ptr<TextureResource> texture)
{
	this->textureResource = texture; 
}

shared_ptr<TextureResource> GraphicsNode::GetTextureResource() const
{
	return this->textureResource;
}

void GraphicsNode::SetTransform(const mat4& transform)
{
	this->transform = transform; 
}

const mat4& GraphicsNode::GetTransform() const
{
	return this->transform; 
	
}

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

void GraphicsNode::Draw()
{
	// test //////////
}
