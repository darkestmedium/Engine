// Vulkan
#define VOLK_IMPLEMENTATION
#define VMA_IMPLEMENTATION
#define VMA_STATIC_VULKAN_FUNCTIONS 0
#define VMA_DYNAMIC_VULKAN_FUNCTIONS 1


#include "vk_engine.h"
#include "ProgramConfig.h"

#include <iostream>
#include <filesystem>




void GetPlatformStr(void)
{
	#if defined(__linux__)
		fmt::println("Main: __linux__ is defined.");
	#elif defined(_WIN32)
		fmt::println("Main: _WIN32 is defined.");
	#elif defined(__APPLE__)
		fmt::println("Main: __APPLE__ is defined.");
	#else
		fmt::println("Main: Unknown platform.");
	#endif
}


int main(int argc, char* argv[])
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
		GetPlatformStr();
		fmt::println("Main: Current working directory: {}", std::filesystem::current_path().c_str());
	}

	// Init Engine
	VulkanEngine engine(args);

	engine.init();
	
	engine.run();

	// engine.Deinitialize();

	return 0;
}
