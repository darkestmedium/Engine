#pragma once

#include "vk_types.h"




class Vulkan
{
public:



	// Getters
	static const char *GetName();
	static bool Initialize();
	static bool IsInitialized();

	// static void Deinitialize();


private:

	static bool bIsInitialized;


	static bool Load();
	static bool CreateInstance();
	static bool CreateMemoryAllocator();


};
