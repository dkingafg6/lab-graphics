#--------------------------------------------------------------------------
# shaders
#--------------------------------------------------------------------------
SET(files_shaders
	vertexShader.vert
	fragmentShader.frag
)
SOURCE_GROUP("shaders" FILES ${files_shaders})

SET(files_pch ../config.h ../config.cc)
SOURCE_GROUP("pch" FILES ${files_pch})
ADD_LIBRARY(shaders STATIC ${files_shaders} ${files_pch})
TARGET_PCH(shaders ../)
ADD_DEPENDENCIES(core glew)
TARGET_LINK_LIBRARIES(shaders PUBLIC engine exts glew)
