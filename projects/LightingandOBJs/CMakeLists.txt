#--------------------------------------------------------------------------
# LightingandOBJsproject
#--------------------------------------------------------------------------

PROJECT(LightingandOBJs)
FILE(GLOB shader_graphic_nodes_headers code/*.h)
FILE(GLOB shader_graphic_nodes_sources code/*.cc)

SET(files_shader_graphic_nodes ${shader_graphic_nodes_headers} ${shader_graphic_nodes_sources})
SOURCE_GROUP("Lighting and OBJs" FILES ${files_shader_graphic_nodes})

ADD_EXECUTABLE(LightingandOBJs ${files_shader_graphic_nodes})
TARGET_LINK_LIBRARIES(LightingandOBJs core render)
ADD_DEPENDENCIES(LightingandOBJs core render)