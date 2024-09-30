
#define STB_IMAGE_IMPLEMENTATION
#include <config.h>
#include <render/stb_image.h>
#include <GL/glew.h>
#include <render/TextureResource.h>


TextureResource::TextureResource() 
{

}	
TextureResource::~TextureResource()
{

}
void TextureResource::loadFromFile(const char* filename)
{
	unsigned char* bytes = stbi_load(filename, &width, &height, &nrchannels, 0); 

	// gernerate textrur and bind
	glGenTextures(1, &textureID); 
	glActiveTexture(GL_TEXTURE0); 
	glBindTexture(GL_TEXTURE_2D, textureID);

	// texture filtrering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	// texture wrapping 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	// upload data to GPU
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);

	stbi_image_free(bytes); 
	glBindTexture(GL_TEXTURE_2D, 0); 

	

}

void TextureResource::Bind(unsigned int unit = 0)
{
	glActiveTexture(GL_TEXTURE0 + unit); 
	glBindTexture(GL_TEXTURE_2D, textureID); 
}





void Cleanup() 
{

}

