//------------------------------------------------------------------------------
// main.cc
// (C) 2015-2022 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------

//#define STB_IMAGE_IMPLEMENTATION
//#include "render/stb_image.h"
#include "config.h"
#include "exampleapp.h"
#include "render/TextureResource.h"
#include"render/Camera.h"
#include <iostream>

//#include "vec4.h"
//#include "vec3.h"

//------------------------------------------------------------------------------
/**
*/
int
main(int argc, const char** argv)
{
	Example::ExampleApp app;
	if (app.Open())
	{
		// textureresouce object. 
		TextureResource textureResource; 

		// attempt to load texture 
		if (!textureResource.loadFromFile("../projects/graphic/texture/lizard.png"))
		{
			std::cerr << "Error loading texture!" << std::endl;
			return -1; // if the textureload fails exit. 

		}

		// when program came here means the texture loaded successfully 
		std::cout << " Texture loaded successfuly! " << std::endl;


		app.Run(); 

		// cleanup before closing 
		textureResource.Cleanup(); // clean up 
		app.Close();

		//app.Run();
		//app.Close();
	}
	app.Exit();	



	return app.ExitCode();
}