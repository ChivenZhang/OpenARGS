cmake_minimum_required (VERSION 3.8)

add_library(OpenARG STATIC
	OpenARG.h
	Private/OpenARG.cpp
)
target_include_directories(OpenARG PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})