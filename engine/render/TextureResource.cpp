
#include <config.h>
#include <GL/glew.h>
#include <cstdio>
#include <render/TextureResource.h>
#include <render/stb_image.h>
#define STB_IMAGE_IMPLEMENTATION
#include <render/stb_image.h>



TextureResource::TextureResource()
{
	textureID = 0;
	width = 0; 
	height = 0; 
	nrchannels = 0; 
		

}	
TextureResource::~TextureResource()
{
	Cleanup(); 

}
bool TextureResource::loadFromFile(const char* filename)
{
	 //load image with stb_load

	// just for test if statement here comment out 
	unsigned char* bytes = stbi_load(filename, &width, &height, &nrchannels, 0);
	if (!bytes) 
	{
		fprintf(stderr, " Failed to load texture: %s\n", filename); 
		
		return false; // return false if loading fails

	}

	// check the texture before uploading if it support 3 or 4 channel!. 
	GLenum format;
	if (nrchannels == 3)
		format = GL_RGB;
	else if (nrchannels == 4)
		format = GL_RGBA;
	else
	{
		std::cerr << "The texture's format not supported " << std::endl;
		stbi_image_free(bytes);
		return false;
	}

	// generate texture and bind
	glGenTextures(1, &textureID); 
	glActiveTexture(GL_TEXTURE0); 
	//texture->Bind(); 
	glBindTexture(GL_TEXTURE_2D, textureID);

	// upload texture's data. 
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, bytes);
	glGenerateMipmap(GL_TEXTURE_2D); 
	
	// texture wrapping 
	// here is different rapping mode.
	// GL_REPEAT= that repeat the texture;
	// GL_MIRRORED_REPEAT=  that mirroring and repeat. 
	// GL_CLAMP_TO_EDAGE=  that press from both side to see clear just in edge, 
	// GL_CLAMP_TO_BORDER=  that clipping the edge just see to clamp. 
	// inside the par-antes(Specifies the texture target, what option we want to set, wrapping mode. ) 

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// texture filtering 
	//GL_LINEAR = produces a smoother pattern where the individual pixels are less visible.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);




	// clean the image some loaded. 
	stbi_image_free(bytes); 
	// unbind texture. 
	glBindTexture(GL_TEXTURE_2D, 0); 

	return true; 



	

}

void TextureResource::Bind(unsigned int unit) const
{
	glActiveTexture(GL_TEXTURE0 + unit); 
	glBindTexture(GL_TEXTURE_2D, this->textureID); 
}

void TextureResource::Cleanup()
{
	if (this->textureID != 0) {
		glDeleteTextures(1, &textureID); // delete the opengl texture
		this->textureID = 0; //reset textureid to 0, 
	}
}
