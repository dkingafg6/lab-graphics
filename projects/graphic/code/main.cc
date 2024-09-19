//------------------------------------------------------------------------------
// main.cc
// (C) 2015-2022 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------

//#define STB_IMAGE_IMPLEMENTATION
//#include "render/stb_image.h"
#include "config.h"
#include "exampleapp.h"
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
		app.Run();
		app.Close();
	}
	app.Exit();	



	return app.ExitCode();
}