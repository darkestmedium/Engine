#include <vk_engine.h>

#include <iostream>
#include <filesystem>

#define FMT_HEADER_ONLY
#include <fmt/core.h>




int main(int argc, char* argv[])
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

	fmt::println("Main: Current working directory: {}", std::filesystem::current_path().c_str());

	VulkanEngine engine;

	engine.init();	
	
	engine.run();	

	engine.cleanup();	

	return 0;
}
