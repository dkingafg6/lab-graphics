#--------------------------------------------------------------------------
# graphic project
#--------------------------------------------------------------------------

PROJECT(graphic)
FILE(GLOB graphic_headers code/*.h)
FILE(GLOB graphic_sources code/*.cc)

SET(files_graphic ${graphic_headers} ${graphic_sources})
SOURCE_GROUP("graphic" FILES ${files_graphic})

ADD_EXECUTABLE(graphic ${files_graphic})
TARGET_LINK_LIBRARIES(graphic core render)
ADD_DEPENDENCIES(graphic core render)