cmake_minimum_required (VERSION 3.8)
project(OpenARGS)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR})
set(OPENARGS_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE STRING "OpenARGS Source Path")

option(OPENARGS_ENABLE_SAMPLE "Enable Sample Compile" OFF)

include_directories(${OPENARGS_SOURCE_DIR})

add_subdirectory(OpenARGS)

if(OPENARGS_ENABLE_SAMPLE)

add_executable(Sample
	main.cpp
		../../Sample/test.cpp
)
target_include_directories(Sample PRIVATE ${CMAKE_SOURCE_DIR}/OpenARGS)
target_link_libraries(Sample OpenARGS)

endif()