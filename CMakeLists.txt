cmake_minimum_required(VERSION 3.8)

project(Engine
	VERSION 0.0.1
	DESCRIPTION "Legacy Vulkan game engine."
	HOMEPAGE_URL "https://vkguide.dev/docs/old_vkguide/"
)

find_package(Vulkan REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set output directories for binaries
# Set the output directories for the executable and libraries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/Binaries/Debug")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/Binaries/Debug")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/Binaries/Release")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/Binaries/Release")

set(SHADER_OUTPUT_DIR "${PROJECT_SOURCE_DIR}/Binaries/${CMAKE_BUILD_TYPE}/Shaders")

add_subdirectory(Source)
