#include "VulkanDynamic.h"
#include <cstdint>

#if RHI_VK

#include <vulkan/vulkan.h>
#include <vulkan/vulkan.hpp>

#pragma comment(lib,"vulkan-1.lib")

#include "RHI/RHIDefinitions.h"

#include "VulkanDevice.h"
#include "VulkanSwapchain.h"
#include "VulkanBuffer.h"
#include "VulkanCommandBuffer.h"
#include "VulkanCommandQueue.h"
#include "VulkanShader.h"
#include "VulkanDescriptorHeap.h"
#include "VulkanDescriptorLayout.h"
#include "VulkanDescriptorView.h"



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
		// Windows依存
		swapchain->CreateSurface(desc.hWnd);

		swapchain->CreateSwapchain();
		return swapchain;
	}
	
	RHIBuffer* VulkanDynamic::CreateBuffer(RHIBufferDesc& desc)
	{
		VulkanBuffer* buffer = new VulkanBuffer(mDevice, desc.Stride, desc.Size, desc.Usage);
		buffer->CreateObject();
		return buffer;
	}

	RHITexture* VulkanDynamic::CreateTexture(RHITextureDesc& desc)
	{
		return nullptr;
	}
	
	RHICommandBuffer* VulkanDynamic::CreateCommandBuffer(RHICommandBufferDesc& desc)
	{
		VulkanCommandBuffer::InitializeExtension(mDevice);

		VulkanCommandBuffer* buffer = new VulkanCommandBuffer(mDevice);
		buffer->Create(desc.Count);
		return buffer;
	}

	RHICommandQueue* VulkanDynamic::CreateCommandQueue(RHICommandQueueDesc& desc)
	{
		VulkanCommandQueue* queue = new VulkanCommandQueue(mDevice);
		queue->Create(0);
		return queue;
	}

	RHIShader* VulkanDynamic::CreateShader(RHIShaderDesc& desc)
	{
		VulkanShader* shader = new VulkanShader(mDevice);
		shader->Create(desc.path);
		return shader;
	}

	RHIDescriptorHeap* VulkanDynamic::CreateDescriptorHeap(RHIDescriptorHeapDesc& desc)
	{
		RHICreate(VulkanDescriptorHeap);
	}

	RHIDescriptorLayout* VulkanDynamic::CreateDescriptorLayout(RHIDescriptorLayoutDesc& desc)
	{
		RHICreate(VulkanDescriptorLayout);
	}

	RHIDescriptorView* VulkanDynamic::CreateDescriptorView(RHIDescriptorViewDesc& desc)
	{
		RHICreate(VulkanDescriptorView);
	}
}

#endif