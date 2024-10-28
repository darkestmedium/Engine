// vulkan_guide.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include "ProgramConfig.h"


#include <vk_types.h>
#include <vk_initializers.h>
#include <vk_mesh.h>

#include "Camera.h"




class PipelineBuilder
{
public:
	std::vector<VkPipelineShaderStageCreateInfo> _shaderStages;
	VkPipelineVertexInputStateCreateInfo _vertexInputInfo;
	VkPipelineInputAssemblyStateCreateInfo _inputAssembly;
	VkViewport _viewport;
	VkRect2D _scissor;
	VkPipelineRasterizationStateCreateInfo _rasterizer;
	VkPipelineColorBlendAttachmentState _colorBlendAttachment;
	VkPipelineMultisampleStateCreateInfo _multisampling;
	VkPipelineLayout _pipelineLayout;
	VkPipelineDepthStencilStateCreateInfo _depthStencil;
	VkPipeline build_pipeline(VkDevice device, VkRenderPass pass);
};


struct DeletionQueue
{
	std::deque<std::function<void()>> deletors;

	void push_function(std::function<void()>&& function)
	{
		deletors.push_back(function);
	}

	void flush()
	{
		// Reverse iterate the deletion queue to execute all the functions
		for (auto it = deletors.rbegin(); it != deletors.rend(); it++)
		{
			(*it)(); // call functors
		}

		deletors.clear();
	}
};


struct Material
{
	VkDescriptorSet textureSet{VK_NULL_HANDLE};
	VkPipeline pipeline;
	VkPipelineLayout pipelineLayout;
};


struct Texture
{
	AllocatedImage image;
	VkImageView imageView;
};


struct RenderObject
{
	Mesh *mesh;
	Material *material; 
	glm::mat4 transformMatrix;
};


struct GPUCameraData
{
	glm::mat4 view;
	glm::mat4 proj;
	glm::mat4 viewproj;
	glm::vec3 pos;
	glm::vec3 nearPoint;
	glm::vec3 farPoint;
};


struct GPUSceneData
{
	glm::vec4 fogColor; // w is for exponent
	glm::vec4 fogDistances; //x for min, y for max, zw unused.
	glm::vec4 ambientColor;
	glm::vec4 sunlightDirection; //w for sun power
	glm::vec4 sunlightColor;
};


struct GPUObjectData
{
	glm::mat4 modelMatrix;
};


struct FrameData
{
	VkSemaphore _presentSemaphore, _renderSemaphore;
	VkFence _renderFence;	

	VkCommandPool _commandPool;
	VkCommandBuffer _mainCommandBuffer;

	AllocatedBuffer cameraBuffer;
	VkDescriptorSet globalDescriptor;

	AllocatedBuffer objectBuffer;
	VkDescriptorSet objectDescriptor;
};


struct UploadContext
{
	VkFence _uploadFence;
	VkCommandPool _commandPool;
	VkCommandBuffer _commandBuffer;
};


constexpr unsigned int FRAME_OVERLAP = 2;


class VulkanEngine
{
public:

	// Constructors
	VulkanEngine(ProgramConfig &args)
		: mArgs(args)
		, bIsInitialized(false)
	{};

	// Destructors
	~VulkanEngine() {Deinitialize();};
		
	ProgramConfig &mArgs;

	bool bIsInitialized;
	int _frameNumber{ 0 };
	int _displayGrid{ 0 };

	VkExtent2D _windowExtent;

	struct SDL_Window *_window{ nullptr };

	VkInstance _instance;
	VkDebugUtilsMessengerEXT _debug_messenger;
	VkPhysicalDevice _chosenGPU;
	VkDevice _device;

	// CAMERA
	Camera mMainCamera;
	GPUCameraData mCameraData;

	VkSemaphore _presentSemaphore, _renderSemaphore;
	VkFence _renderFence;

	VkQueue _graphicsQueue;
	uint32_t _graphicsQueueFamily;
	
	VkRenderPass _renderPass;

	VkSurfaceKHR _surface;
	VkSwapchainKHR _swapchain;
	VkFormat _swachainImageFormat;

	std::vector<VkFramebuffer> _framebuffers;
	std::vector<VkImage> _swapchainImages;
	std::vector<VkImageView> _swapchainImageViews;

	DeletionQueue _mainDeletionQueue;

	// Pipelines
	VkPipelineLayout mGridPipelineLayout;
	VkPipeline mGridPipeline;

	// VkPipelineLayout _meshPipelineLayout;
	// VkPipeline _meshPipeline;

	Mesh _monkeyMesh;

	VmaAllocator _allocator; //vma lib allocator

	//depth resources
	VkImageView _depthImageView;
	AllocatedImage _depthImage;

	//the format for the depth image
	VkFormat _depthFormat;

	//frame storage
	FrameData _frames[FRAME_OVERLAP];

	//getter for the frame we are rendering to right now.
	FrameData &get_current_frame();

	const char *GetName() const;

	//initializes everything in the engine
	void init();

	//shuts down the engine
	void Deinitialize();

	//draw loop
	void draw();

	//run main loop
	void run();

	UploadContext _uploadContext;

	AllocatedBuffer create_buffer(size_t allocSize, VkBufferUsageFlags usage, VmaMemoryUsage memoryUsage);
	void immediate_submit(std::function<void(VkCommandBuffer cmd)> &&function);

	//texture hashmap
	std::unordered_map<std::string, Texture> _loadedTextures;
	void load_images();

	// Default array of renderable objects
	std::vector<RenderObject> _renderables;

	std::unordered_map<std::string,Material> _materials;
	std::unordered_map<std::string,Mesh> _meshes;

	VkDescriptorSetLayout _globalSetLayout;
	VkDescriptorSetLayout _objectSetLayout;
	VkDescriptorSetLayout _singleTextureSetLayout;

	VkDescriptorPool _descriptorPool;
	VkPhysicalDeviceProperties _gpuProperties;

	GPUSceneData _sceneParameters;
	AllocatedBuffer _sceneParameterBuffer;
	size_t pad_uniform_buffer_size(size_t originalSize);

	//create material and add it to the map
	Material *create_material(VkPipeline pipeline, VkPipelineLayout layout,const std::string &name);
	//returns nullptr if it can't be found
	Material *get_material(const std::string &name);
	//returns nullptr if it can't be found
	Mesh *get_mesh(const std::string &name);


private:

	void init_vulkan();

	void init_swapchain();

	void init_default_renderpass();

	void init_framebuffers();

	void init_commands();

	void init_sync_structures();

	void init_descriptors();

	void init_pipelines();

	// Loads a shader module from a spir-v file. Returns false if it errors
	bool load_shader_module(const char* filePath, VkShaderModule *outShaderModule);

	void load_meshes();

	void upload_mesh(Mesh &mesh);

	void update_scene();


	// Our draw function
	void draw_objects(VkCommandBuffer cmd, RenderObject *first, int count);

	void init_scene();

};


