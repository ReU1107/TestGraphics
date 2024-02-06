#include "VulkanDynamic.h"
#include <cstdint>

#if RHI_VK

#include <vulkan/vulkan.h>
#include <vulkan/vulkan.hpp>

#pragma comment(lib,"vulkan-1.lib")

#include "VulkanDevice.h"
#include "VulkanSwapchain.h"
#include "VulkanBuffer.h"
#include "VulkanCommandBuffer.h"
#include "VulkanCommandQueue.h"

#include "RHI/RHIDefinitions.h"


namespace Alpha
{
	VulkanDynamic::VulkanDynamic()
	{
		mDevice = new VulkanDevice();

		SetInstance(this);

		//vk::CommandBuffer c;
		//c.pipelineBarrier(, , , nullptr, nullptr,, nullptr);

	}

	VulkanDynamic::~VulkanDynamic()
	{
		delete mDevice;
	}
	
	void VulkanDynamic::Init()
	{
	}

	RHISwapchain* VulkanDynamic::CreateSwapchain(RHISwapchainDesc& desc)
	{
		VulkanSwapchain* swapchain = new VulkanSwapchain(mDevice);
		// WindowsˆË‘¶
		swapchain->CreateSurface(desc.hWnd);

		swapchain->CreateSwapchain();
		return swapchain;
	}
	
	RHIBuffer* VulkanDynamic::CreateBuffer(RHIBufferDesc& desc)
	{
		VulkanBuffer* buffer = new VulkanBuffer(mDevice, desc.Stride, desc.Size, desc.Usage);
		return buffer;
	}

	RHITexture* VulkanDynamic::CreateTexture(RHITextureDesc& desc)
	{
		return nullptr;
	}
	
	RHICommandBuffer* VulkanDynamic::CreateCommandBuffer(RHICommandBufferDesc& desc)
	{
		VulkanCommandBuffer* buffer = new VulkanCommandBuffer(mDevice);
		buffer->Create(3);
		return buffer;
	}

	RHICommandQueue* VulkanDynamic::CreateCommandQueue(RHICommandQueueDesc& desc)
	{
		VulkanCommandQueue* queue = new VulkanCommandQueue(mDevice);
		queue->Create(0);
		return queue;
	}
}

#endif