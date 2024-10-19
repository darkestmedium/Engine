#pragma once

#include <argparse.hpp>

#include <iostream>
#include <vector>

#define FMT_HEADER_ONLY
#include <fmt/core.h>


struct ProgramConfig : public argparse::Args
{
	// Constructor - kind off. 
	ProgramConfig()
	{
		commandName = "VulkanEngine";

		requiredValidationLayers = {
			"VK_LAYER_KHRONOS_validation"
		};
		requiredInstanceExtensions = {
			"VK_KHR_get_physical_device_properties2",
			"VK_KHR_surface",
		};
		requiredDeviceExtensions = {
			"VK_KHR_swapchain",
			"VK_KHR_video_queue",
			"VK_KHR_video_decode_queue",
			"VK_KHR_video_decode_h264",
				"VK_KHR_synchronization2",
			"VK_KHR_sampler_ycbcr_conversion",
		};
		requiredDeviceQueueFlags = {
			1,  // VK_QUEUE_GRAPHICS_BIT = 0x00000001
			2048,  // VK_QUEUE_PRESENT_BIT = 0x00000800
			32,  // VK_QUEUE_VIDEO_DECODE_BIT_KHR = 0x00000020
				// video queues must also support transfer, and we want a video decode queue
				4,  // VK_QUEUE_TRANSFER_BIT = 0x00000004
		};
	}

	std::string &programName = kwarg("pn,programName", "Name of the program, will be displayed in window.").set_default("Vulkan Engine");
	uint32_t &initialWidth   = kwarg("iw,initialWidth", "Initial width of the window.").set_default(1920);
	uint32_t &initialHeight  = kwarg("ih,initialHeight", "Initial height of the window.").set_default(810);

	// uint16_t &msaaSamples       = kwarg("msaa,msaaSamples", "Multisample anti-aliasing.").set_default(8);
	uint16_t &presentMode    = kwarg("pm,presentMode", "Present mode, default is VK_PRESENT_MODE_FIFO_KHR.").set_default(2);
	uint16_t &framesInFlight = kwarg("fif,framesInFlight", "Amount of frames in flight, default is 2.").set_default(2);

	bool &verbose = flag("v,verbose", "Toggle verbose mode.");
	bool &help    = flag("h,help", "Display usage");

	std::string commandName;

	std::vector<const char*> requiredValidationLayers;
	std::vector<const char*> requiredInstanceExtensions;
	std::vector<const char*> requiredDeviceExtensions;
	// std::vector<const char*> requiredDeviceFeautres;
	std::vector<int>         requiredDeviceQueueFlags;

	void DisplayHelp()
	{
		fmt::print(
			"Flags:\n"
			"  --pn  --programName (string):  Name of the program, will be displayed in window.\n"
			"  --fp  --filePath (string):  Path to the file, ex. 'image.jpg'.\n"
			"  --v   --verbose (flag):  Toggle Verbose mode.\n\n"
			"Example usage :\n"
			"  --filePath imgage1.jpg\n"
		);
	};

	// void parseArgs(int argc, const char* const *argv, const bool &raise_on_error=false)
};
