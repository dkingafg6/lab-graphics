#pragma once
#include <GL/glew.h>
#define STB_IMAGE_IMPLEMENTATION
#include <core/stb_image.h>


class TextureResource
{
private:
	GLuint textureID;
public:
	TextureResource();
	~TextureResource();

	bool loadFromFile(const char* filename); 
	void Bind(unsigned int unit = 0); 
	void Cleanup(); 


	//GLuint textureID;	
};
