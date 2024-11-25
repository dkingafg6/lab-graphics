#--------------------------------------------------------------------------
# engine
#--------------------------------------------------------------------------

ADD_LIBRARY(engine INTERFACE)
TARGET_INCLUDE_DIRECTORIES(engine INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
TARGET_LINK_LIBRARIES(engine INTERFACE ${OPENGL_LIBS})
ADD_SUBDIRECTORY(core)
ADD_SUBDIRECTORY(render)
ADD_SUBDIRECTORY(texture)
ADD_SUBDIRECTORY(shaders)
ADD_SUBDIRECTORY(OBJFiles)
TARGET_LINK_LIBRARIES(engine INTERFACE core render texture shaders OBJFiles)

SET_TARGET_PROPERTIES(core PROPERTIES FOLDER "engine")
SET_TARGET_PROPERTIES(render PROPERTIES FOLDER "engine")
SET_TARGET_PROPERTIES(texture PROPERTIES FOLDER "engine")
SET_TARGET_PROPERTIES(shaders PROPERTIES FOLDER "engine")
SET_TARGET_PROPERTIES(OBJFiles PROPERTIES FOLDER "engine")

