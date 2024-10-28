#include "Vulkan.h"




bool Vulkan::bIsInitialized = false;




const char *Vulkan::GetName()
{
	return "Vulkan";	
};


bool Vulkan::IsInitialized()
{
	return bIsInitialized;	
};


bool Vulkan::Initialize()
{
	if (bIsInitialized)
	{
		LOG(INFO, "{}: Vulkan is already initialized.", GetName());
	}

	if (!Load())
	{
		return false;
	}

	LOG(SUCCESS, "{}: Vulkan was initialized successsfully.", GetName());

	bIsInitialized = true;

	return bIsInitialized;
}


bool Vulkan::Load()
{
  if (volkInitialize() != VK_SUCCESS)
	{
    LOG(FATAL, "{}: Volk failed to load.", GetName());
    return false;
  }

  LOG(SUCCESS, "{}: Volk loaded successfully.", GetName());

	return true;
};


bool Vulkan::CreateInstance()
{
	return true;
};


bool Vulkan::CreateMemoryAllocator()
{
	return true;
};


