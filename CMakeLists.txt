cmake_minimum_required (VERSION 3.8)
project(OpenARG)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR})
set(OPENARG_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE STRING "OpenARG Source Path")

option(OPENARG_ENABLE_SAMPLE "Enable Sample Compile" OFF)

include_directories(${OPENARG_SOURCE_DIR})

add_subdirectory(OpenARG)

if(OPENARG_ENABLE_SAMPLE)

add_executable(Sample
	main.cpp
)
target_include_directories(Sample PRIVATE ${CMAKE_SOURCE_DIR}/OpenARG)
target_link_libraries(Sample OpenARG)

endif()