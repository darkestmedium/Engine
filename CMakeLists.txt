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
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/Binaries/Release")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/Binaries/Debug")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/Binaries/Release")

set(SHADER_OUTPUT_DIR "${PROJECT_SOURCE_DIR}/Binaries/${CMAKE_BUILD_TYPE}/Shaders")
message("Shaders output dir:  " ${SHADER_OUTPUT_DIR})



add_subdirectory(Source)


# Define the shader directory variable
set(SHADER_DIR "${PROJECT_SOURCE_DIR}/Shaders")

# find_program(GLSL_VALIDATOR glslangValidator HINTS /usr/bin /usr/local/bin $ENV{VULKAN_SDK}/Bin/ $ENV{VULKAN_SDK}/Bin32/)

# # Use SHADER_DIR variable for shader file search
# file(GLOB_RECURSE GLSL_SOURCE_FILES
#   "${SHADER_DIR}/*.frag"
#   "${SHADER_DIR}/*.vert"
#   "${SHADER_DIR}/*.comp"
# )

# foreach(GLSL ${GLSL_SOURCE_FILES})
#   message(STATUS "BUILDING SHADERS")
#   get_filename_component(FILE_NAME ${GLSL} NAME)
#   set(SPIRV "${SHADER_DIR}/${FILE_NAME}.spv")
#   message(STATUS ${GLSL})
#   add_custom_command(
#     OUTPUT ${SPIRV}
#     COMMAND ${GLSL_VALIDATOR} -V ${GLSL} -o ${SPIRV}
#     DEPENDS ${GLSL})
#   list(APPEND SPIRV_BINARY_FILES ${SPIRV})
# endforeach(GLSL)

# # Create custom target for building shaders
# add_custom_target(
#   Shaders 
#   DEPENDS ${SPIRV_BINARY_FILES}
# )

# Custom target to build both the Engine and Shaders
# add_custom_target(BuildAll DEPENDS Engine Shaders)
