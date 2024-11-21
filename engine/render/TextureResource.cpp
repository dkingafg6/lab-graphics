
#include <config.h>
#include <GL/glew.h>
#include <cstdio>
#include <render/TextureResource.h>
#include <render/stb_image.h>
#define STB_IMAGE_IMPLEMENTATION
#include <render/stb_image.h>



TextureResource::TextureResource()
{
	this->textureID = 0;
	this->width = 0;
	this->height = 0;
	this->nrchannels = 0;
	this->isTexLoaded = false;
		

}	
TextureResource::~TextureResource()
{
	Cleanup(); 

}
void TextureResource::loadFromFile(const char* filename)
{
	unsigned char* bytes = stbi_load(filename, &width, &height, &nrchannels, 0);
	if (bytes == nullptr) 
	{
		std::cerr << " Failed to load texture: " << filename << std::endl; 

		isTexLoaded = false;
		return;
	}

	// generate texture and bind
	glGenTextures(1, &textureID);  
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// texture filtering 
	//GL_LINEAR = produces a smoother pattern where the individual pixels are less visible.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// upload texture's data. 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
	glGenerateMipmap(GL_TEXTURE_2D); 

	// clean the image some loaded. 
	stbi_image_free(bytes); 
	// unbind texture. 
	glBindTexture(GL_TEXTURE_2D, 0); 

	isTexLoaded = true;

}

void TextureResource::Bind(unsigned int unit)
{
	if (isTexLoaded)
	{
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, textureID);
	}
	
}
GLuint TextureResource::getTextureID()
{
	return this->textureID;
}

void TextureResource::Cleanup()
{
	if (this->textureID != 0) 
	{
		glDeleteTextures(1, &textureID); // delete the opengl texture
		this->textureID = 0; //reset textureid to 0, 
	}
}
