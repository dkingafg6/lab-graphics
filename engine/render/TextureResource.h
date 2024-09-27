#pragma once

#include <string>
#include <iostream>

using namespace std;


class TextureResource
{



public:
	GLuint textureID;
	//GLuint textureID

	TextureResource();
    ~TextureResource();

	void loadFromFile(const char* filename);
	void bind(); 
	void Cleanup(); 

	int width;
	int height;
	int nrchannels;


		
};
