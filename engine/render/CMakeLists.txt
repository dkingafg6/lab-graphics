#--------------------------------------------------------------------------
# render
#--------------------------------------------------------------------------

SET(files_render_display
	window.h
	window.cc
	grid.h
	grid.cc
	Camera.h
	Camera.cpp
	Meshresource.h
	MeshResource.cpp
	stb_image.h
	TextureResource.h
	TextureResource.cpp 
	WindowWrapper.h 
       	ShaderResource.cpp 
       	ShaderResource.h
      	GraphicsNode.cpp
	GraphicsNode.h
)


SOURCE_GROUP("display" FILES ${files_render_display})

SET(files_render
	${files_render_display}
	${files_render_pch})

SET(files_pch ../config.h ../config.cc)
SOURCE_GROUP("pch" FILES ${files_pch})
ADD_LIBRARY(render STATIC ${files_render} ${files_pch})
TARGET_PCH(render ../)	
ADD_DEPENDENCIES(render glew glfw)
TARGET_LINK_LIBRARIES(render PUBLIC engine exts glew glfw imgui ${OPENGL_LIBS})