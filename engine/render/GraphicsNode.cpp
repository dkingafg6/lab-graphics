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

void GraphicsNode::SetShaderResource(shared_ptr<ShaderResource> shader)
{
	this->shaerResource = shader; 
}

shared_ptr<ShaderResource> GraphicsNode::GetShaderResource() const
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

void GraphicsNode::Draw(const mat4& viewPrjectionMatrix)
{
	//set texture uniform and the unit is 0 
	glUniform1i(textureLoc, 0);


	//	// attributes set the uniform when shader program avtivate. 
	glUniformMatrix4fv(camMatrixLoc, 1, GL_FALSE, (GLfloat*)&viewProjectionMatrix);
	glUniformMatrix4fv(rotationLoc, 1, GL_FALSE, (GLfloat*)&matrix4x4);

	// bind texture to uniform 
	glUniform1i(textureLoc, 0);


	// draw a 3D grid and mesh
	//grid.Draw((GLfloat*)&viewProjectionMatrix); // call the grid's draw function with combined matrix 
	meshResource->BindVBO();
	meshResource->BindIBO();// update the camera based on mouse mouvement. 

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);// render and draw the cube.
	glBindVertexArray(0);
	// test //////////
}
