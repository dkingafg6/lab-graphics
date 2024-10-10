#--------------------------------------------------------------------------
# texture
#--------------------------------------------------------------------------
SET(files_texture
	lizard0.png
	lizard1.png
	lizard2.png
	lizard3.png
	lizard4.png)
SOURCE_GROUP("texture" FILES ${files_texture})

SET(files_pch ../config.h ../config.cc)
SOURCE_GROUP("pch" FILES ${files_pch})
ADD_LIBRARY(texture STATIC ${files_texture} ${files_pch})
TARGET_PCH(texture ../)
ADD_DEPENDENCIES(core glew)
TARGET_LINK_LIBRARIES(texture PUBLIC engine exts glew)
