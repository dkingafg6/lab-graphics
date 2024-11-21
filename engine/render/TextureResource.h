#pragma once

#include <string>
#include <iostream>
#include <GL/glew.h>
#include "render/stb_image.h"

using namespace std;


class TextureResource
{



public:
	TextureResource();
    ~TextureResource();

	void loadFromFile(const char* filename);
	void Bind(unsigned int unit = 0 );
	void Cleanup();

	GLuint getTextureID();

private:
	GLuint textureID;
	bool isTexLoaded;
	int width;
	int height;
	int nrchannels;


		
};
