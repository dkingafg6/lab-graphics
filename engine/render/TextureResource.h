#pragma once
#include <GL/glew.h>
#include <string>
#include <render/stb_image.h>
#include <iostream>

using namespace std;


class TextureResource
{
public:
	GLuint textureID;
	//GLuint textureID;

	TextureResource();
    ~TextureResource();

	bool loadFromFile(const std::string& filename);
	void Bind(unsigned int unit);
                                    
	void Cleanup(); 

		
};
