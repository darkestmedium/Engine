# find_package(Vulkan REQUIRED)

# add_library(vulkan INTERFACE)
# target_include_directories(vulkan INTERFACE vulkan)



# Add Volk as an INTERFACE library
add_library(volk INTERFACE)
target_include_directories(volk INTERFACE vulkan)

# # If you have Vulkan SDK installed and still want to link Vulkan for certain use cases
# # You can still specify the Vulkan library manually, if needed:
# target_link_libraries(volk INTERFACE vulkan)





add_library(argparse INTERFACE)
target_include_directories(argparse INTERFACE argparse)
# fetch latest argparse
# include(FetchContent)
# FetchContent_Declare(
# 	argparse
# 	GIT_REPOSITORY https://github.com/p-ranav/argparse.git
# )
# FetchContent_MakeAvailable(argparse)


add_library(fmt INTERFACE)

#add_library(sdl2 INTERFACE)
#target_include_directories(sdl2 INTERFACE $ENV{VULKAN_SDK}/Include/SDL2 )
#target_link_directories(sdl2 INTERFACE $ENV{VULKAN_SDK}/Lib )
#target_link_libraries(sdl2 INTERFACE SDL2 SDL2main)


add_subdirectory(SDL EXCLUDE_FROM_ALL)


# add_subdirectory(fastgltf)


# Vulkan Bootstrap
add_library(vkbootstrap STATIC)
target_sources(vkbootstrap PRIVATE 
  vulkan/vkbootstrap/VkBootstrap.h
  vulkan/vkbootstrap/VkBootstrap.cpp
)
target_include_directories(vkbootstrap PUBLIC vulkan/vkbootstrap)
target_link_libraries(vkbootstrap PUBLIC vulkan $<$<BOOL:UNIX>:${CMAKE_DL_LIBS}>)
set_property(TARGET vkbootstrap PROPERTY CXX_STANDARD 20)


# Tiny Obj Loader
add_library(tinyobjloader STATIC)
target_sources(tinyobjloader PRIVATE 
	tinyobjloader/tiny_obj_loader.h
	tinyobjloader/tiny_obj_loader.cc
)
target_include_directories(tinyobjloader PUBLIC tinyobjloader)


# STB Image
add_library(stb_image INTERFACE)
target_include_directories(stb_image INTERFACE fmt)


# Vulkan Memory Allocator
add_library(vma INTERFACE)
target_include_directories(vma INTERFACE vulkan/vma)


# OGL Math Library
add_library(glm INTERFACE)
target_include_directories(glm INTERFACE glm)


# IMGUI
add_library(imgui STATIC)
target_include_directories(imgui PUBLIC imgui)
target_sources(imgui PRIVATE 
  imgui/imgui.h
  imgui/imgui.cpp
  imgui/imgui_demo.cpp
  imgui/imgui_draw.cpp
  imgui/imgui_widgets.cpp
  imgui/imgui_tables.cpp
  imgui/imgui_impl_vulkan.cpp
  imgui/imgui_impl_sdl3.cpp
)
target_link_libraries(imgui PUBLIC vulkan SDL3::SDL3)
target_include_directories(stb_image INTERFACE stb_image)
