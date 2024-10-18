# add_subdirectory(ThirdParty)
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	add_compile_options(-Wno-nullability-completeness)
	add_compile_options(-Wno-deprecated-this-capture)
	add_compile_options(-Wno-unused-variable)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	add_compile_options(/wd4458)  # Example MSVC warning code
endif()


# Add source to this project's executable.
add_executable(Engine 
	ProgramConfig.h
	main.cpp
	vk_engine.cpp
	vk_engine.h
	vk_initializers.cpp
	vk_initializers.h
	vk_mesh.cpp
	vk_mesh.h
	vk_types.h
)

# set_property(TARGET Engine PROPERTY CXX_STANDARD 17)
target_compile_definitions(Engine PUBLIC GLM_FORCE_DEPTH_ZERO_TO_ONE)
target_include_directories(Engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(Engine PUBLIC
	Vulkan::Vulkan
	vma
	vkbootstrap
	glm
	tinyobjloader
	stb_image
	SDL3::SDL3
	imgui
	fmt
	argparse
)

add_dependencies(Engine Shaders)

target_precompile_headers(Engine PUBLIC
	<optional>
	<vector>
	<memory>
	<string>
	<vector>
	<unordered_map>
	<glm/mat4x4.hpp>
	<glm/vec4.hpp>
	<vulkan/vulkan.h>
)


if (WIN32)
	add_custom_command(TARGET Engine POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different 
			$<TARGET_RUNTIME_DLLS:Engine>
			$<TARGET_FILE_DIR:Engine>
		COMMAND_EXPAND_LISTS
	)
endif()

# Custom target to build both the Engine and Shaders
# add_custom_target(BuildAll DEPENDS Engine Shaders)

