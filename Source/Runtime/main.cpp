// Vulkan
#define VOLK_IMPLEMENTATION
#define VMA_IMPLEMENTATION
#define VMA_STATIC_VULKAN_FUNCTIONS 0
#define VMA_DYNAMIC_VULKAN_FUNCTIONS 1



#include "vk_engine.h"
#include "ProgramConfig.h"

#include <iostream>
#include <filesystem>


const char *GetName()
{
	return "Main";
}


void PrintPlatformStr(void)
{
	#if defined(__linux__)
		LOG_INFO("{}: __linux__ is defined.", GetName());
	#elif defined(_WIN32)
		LOG_INFO("{}: _WIN32 is defined.", GetName());
	#elif defined(__APPLE__)
		LOG_INFO("{}: __APPLE__ is defined.", GetName());
	#else
		LOG_INFO("{}: Unknown platform.", GetName());
	#endif
}


int main(int argc, char *argv[])
{
	ProgramConfig args = argparse::parse<ProgramConfig>(argc, argv);

	if (args.help)
	{
		args.DisplayHelp();
		return 0;
	}

	if (args.verbose)
	{
		#define DEBUG
		args.print();  // Prints all variables
		PrintPlatformStr();

		LOG_INFO("{}: Current working directory: {}", GetName(), std::filesystem::current_path().c_str())
	}

	VulkanEngine engine(args);

	engine.init();
	
	engine.run();

	return 0;
}
