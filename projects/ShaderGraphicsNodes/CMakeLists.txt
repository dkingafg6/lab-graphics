#--------------------------------------------------------------------------
# ShaderGraphicsNodes project
#--------------------------------------------------------------------------

PROJECT(ShaderGraphicsNodes)
FILE(GLOB shader_graphic_nodes_headers code/*.h)
FILE(GLOB shader_graphic_nodes_sources code/*.cc)

SET(files_shader_graphic_nodes ${shader_graphic_nodes_headers} ${shader_graphic_nodes_sources})
SOURCE_GROUP("ShaderGraphicsNodes" FILES ${files_shader_graphic_nodes})

ADD_EXECUTABLE(ShaderGraphicsNodes ${files_shader_graphic_nodes})
TARGET_LINK_LIBRARIES(ShaderGraphicsNodes core render)
ADD_DEPENDENCIES(ShaderGraphicsNodes core render)