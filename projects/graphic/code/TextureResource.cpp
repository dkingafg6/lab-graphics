#include "TextureResource.h"
#include <iostream>
//#include <core/stb_image.h>

// testing methods 
TextureResource::TextureResource() : textureID(0)
{
}

TextureResource::~TextureResource()
{
	Clearup(); 
}

bool TextureResource::loadFromFile(const char* filename)
{
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Load image using stb_image
    int width, height, nrChannels;
    unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);
    if (!data)
    {
        std::cerr << "Failed to load texture: " << filename << std::endl;
        return false;
    }

    // Determine the format based on the number of channels
    GLenum format;
    switch (nrChannels)
    {
    case 1: format = GL_RED; break;
    case 3: format = GL_RGB; break;
    case 4: format = GL_RGBA; break;
    default:
        std::cerr << "Unsupported number of channels: " << nrChannels << std::endl;
        stbi_image_free(data);
        return false;
    }

    // Upload texture data to GPU
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    // Generate mipmaps
    glGenerateMipmap(GL_TEXTURE_2D);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Free image data
    stbi_image_free(data);

    return textureID;
}



void TextureResource::Bind(unsigned int textureUnit = 0)
{
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D,textureID);

}

void TextureResource::Clearup()
{
    if (textureID) 
    {
        glDeleteTextures(1, &textureID);
        textureID = 0;
    }
}
