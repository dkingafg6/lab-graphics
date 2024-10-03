
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
		fprintf(stderr, " Failed to load texture: %s", filename); 
		return false; // return false if loading fails

	}

	// generate texture and bind
	glGenTextures(1, &textureID); 
	glActiveTexture(GL_TEXTURE0); 
	glBindTexture(GL_TEXTURE_2D, textureID);

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


	// test here if it work!
	//load image with stb_load 
	//unsigned char *data = stbi_load(filename, &width, &height, &nrchannels, 0);
	//if (!data)
	//{
	//	// upload data to GPU
	//	GLenum format = (nrchannels == 3) ? GL_RGB : GL_RGBA;
	//	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	//	glGenerateMipmap(GL_TEXTURE_2D); // generate image. 
	//	
	//}
	//else 
	//{
	//	std::cout << " Failed to load texture : " << std::endl; 

	//}

	// upload data to GPU
	// just for test those three line down comment out
	//GLenum format = (nrchannels == 3) ? GL_RGB : GL_RGBA; 
	//glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, bytes);
	//glGenerateMipmap(GL_TEXTURE_2D); // generate image. 


	// clean upp 
	stbi_image_free(bytes); 
	glBindTexture(GL_TEXTURE_2D, 0); 

	return true; 



	

}

void TextureResource::Bind(unsigned int unit) const
{
	glActiveTexture(GL_TEXTURE0 + unit); 
	glBindTexture(GL_TEXTURE_2D, textureID); 
}

void TextureResource::Cleanup()
{
	if (textureID != 0) {
		glDeleteTextures(1, &textureID); // delete the opengl texture
		textureID = 0; //reset textureid to 0, 
	}
}
