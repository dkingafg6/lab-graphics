#include "TextureResource.h"
#include <iostream>
//#include <core/stb_image.h>

// testing methods 
TextureResource::TextureResource() : textureID(0)
{
}

TextureResource::~TextureResource()
{
	Cleanup(); 
}

bool TextureResource::loadFromFile(const char* filename)
{
   /* glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);*/

    // Load image using stb_image
    int width, height, Channels;
    unsigned char* data = stbi_load(filename, &width, &height, &Channels, 4);
    if (!data)
    {
        std::cerr << "Failed to load texture: " << filename << std::endl;
        return false; 

    }


    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Upload texture data to GPU
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    // Generate mipmaps
    glGenerateMipmap(GL_TEXTURE_2D);


    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Free image data
    stbi_image_free(data);
    return true;

}



void TextureResource::Bind(unsigned int textureUnit)
{
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D,this->textureID);

}


void TextureResource::Cleanup()
{
    if (textureID) 
    {
        glDeleteTextures(1, &textureID);
        textureID = 0;
    }
}
