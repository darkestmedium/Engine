# Set target build directory for shaders
# set(TARGET_BUILD_DIR "${PROJECT_SOURCE_DIR}/Build/${CMAKE_BUILD_TYPE}/Shaders")

# Define the shader directory variable
set(SHADER_SRC_DIR "${PROJECT_SOURCE_DIR}/Source/Shaders")

# Find the glslangValidator program for compiling shaders
find_program(GLSL_VALIDATOR glslangValidator
	HINTS /usr/bin /usr/local/bin $ENV{VULKAN_SDK}/Bin/ $ENV{VULKAN_SDK}/Bin32/
)


# # Create the target build directory if it doesn't exist
file(MAKE_DIRECTORY ${SHADER_OUTPUT_DIR})

# Use SHADER_SRC_DIR variable for shader file search
file(GLOB_RECURSE GLSL_SOURCE_FILES
  "${SHADER_SRC_DIR}/*.frag"
  "${SHADER_SRC_DIR}/*.vert"
  "${SHADER_SRC_DIR}/*.comp"
)


foreach(GLSL ${GLSL_SOURCE_FILES})
  message(STATUS "Compiling shader: ${GLSL}")
  get_filename_component(FILE_NAME ${GLSL} NAME)
  
  # Set the output SPIR-V file in the target build directory
  set(SPIRV "${SHADER_OUTPUT_DIR}/${FILE_NAME}.spv")
	# set(SPIRV "${SHADER_DIR}/${FILE_NAME}.spv")
  
  # Add custom command for compiling the shader
  add_custom_command(
    OUTPUT ${SPIRV}
    COMMAND ${GLSL_VALIDATOR} -V ${GLSL} -o ${SPIRV}
    DEPENDS ${GLSL}
  )
  
  # Append the compiled SPIR-V files to the list
  list(APPEND SPIRV_BINARY_FILES ${SPIRV})
endforeach(GLSL)

# Create a custom target for building shaders
add_custom_target(
  Shaders 
  DEPENDS ${SPIRV_BINARY_FILES}
)

# Custom target to build both the Engine and Shaders
add_custom_target(BuildAll DEPENDS Engine Shaders)
