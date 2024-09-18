#pragma once
#include <GL/glew.h>
#include <string>
#include <core/stb_image.h>
#include <iostream>

using namespace std;


class TextureResource
{
private:
	//GLuint textureID;
public:

	GLuint textureID;

	TextureResource();
	~TextureResource();

	bool loadFromFile(const std::string& filename); 
	void Bind(unsigned int unit); 
	void Cleanup(); 

		
};
