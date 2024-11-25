#--------------------------------------------------------------------------
# OBJFiles
#--------------------------------------------------------------------------
SET(files_OBJFiles
		buddha.obj
                cube.obj)
SOURCE_GROUP("OBJFiles" FILES ${files_OBJFiles})

SET(files_pch ../config.h ../config.cc)
SOURCE_GROUP("pch" FILES ${files_pch})
ADD_LIBRARY(OBJFiles STATIC ${files_OBJFiles} ${files_pch})
TARGET_PCH(OBJFiles ../)
ADD_DEPENDENCIES(core glew)
TARGET_LINK_LIBRARIES(OBJFiles PUBLIC engine exts glew)
