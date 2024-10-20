// vulkan_guide.h : Include file for standard system include files,
// or project specific include files.

#pragma once

// STD
#include <deque>
#include <functional>
#include <fstream>
#include <iostream>
#include <vector>


// Vulkan
// #ifndef VMA_IMPLEMENTATION
// 	#define VMA_IMPLEMENTATION
// #endif

#include <volk/volk.h>
#include <vk_mem_alloc.h>


// GLM
#ifndef GLM_FORCE_RADIANS
	#define GLM_FORCE_RADIANS
#endif

#ifndef GLM_FORCE_DEPTH_ZERO_TO_ONE
	#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#endif

#ifndef GLM_ENABLE_EXPERIMENTAL
	#define GLM_ENABLE_EXPERIMENTAL
#endif

#include <glm/glm.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "glm/gtx/quaternion.hpp"

#include <fmt/core.h>





struct AllocatedBuffer {
	VkBuffer _buffer;
	VmaAllocation _allocation;
};


struct AllocatedImage {
	VkImage _image;
	VmaAllocation _allocation;
};