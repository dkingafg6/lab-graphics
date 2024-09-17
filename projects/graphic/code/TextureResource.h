#pragma once
#include <GL/glew.h>
#define STB_IMAGE_IMPLEMENTATION
#include <core/stb_image.h>


class TextureResource
{
public:
	TextureResource();
	~TextureResource();
	bool loadFromFile(const char* filename); 
	void Bind(unsigned int textureUnit); 
	void Clearup(); 


	GLuint textureID;	
};
