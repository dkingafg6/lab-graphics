#pragma once

#include <string>
#include <iostream>
#include <GL/glew.h>
#include "render/stb_image.h"

using namespace std;


class TextureResource
{



public:
	
	GLuint textureID;
	unsigned int texture; 
	unsigned char* bytes;
	TextureResource();
    ~TextureResource();

	bool loadFromFile(const char* filename);
	void Bind(unsigned int unit = 0 ) const;

private:
	void Cleanup(); 

	int width;
	int height;
	int nrchannels;


		
};
