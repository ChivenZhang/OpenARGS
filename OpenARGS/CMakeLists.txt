add_library(OpenARGS STATIC
	OpenARGS.h
	Private/OpenARGS.cpp
)
target_include_directories(OpenARGS PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})