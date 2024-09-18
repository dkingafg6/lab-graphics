#pragma once
#include <GL/glew.h>
<<<<<<<< HEAD:projects/graphic/code/TextureResource.h
#define STB_IMAGE_IMPLEMENTATION
#include <core/stb_image.h>
========
#include <string>
#include <render/stb_image.h>
#include <iostream>

using namespace std;
>>>>>>>> 352aaaf (update many stb errors):engine/render/TextureResource.h


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
