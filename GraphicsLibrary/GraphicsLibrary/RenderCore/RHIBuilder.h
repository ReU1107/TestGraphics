#pragma once
#include "RHI/RHIDeclarations.h"
#include "RHI/RHIDefinitions.h"

namespace Alpha
{
	class RHIBuilder
	{
	public:
		// 
		static RHIBuffer* CreateBuffer(RHIBufferDesc& desc);
		// 
		static RHITexture* CreateTexture(RHITextureDesc& desc);
		// 
		static RHISwapchain* CreateSwapchain(RHISwapchainDesc& desc);
		// 
		static RHICommandBuffer* CreateCommandBuffer(RHICommandBufferDesc& desc);
		// 
		static RHICommandQueue* CreateCommandQueue(RHICommandQueueDesc& desc);

		static RHIDescriptorHeap* CreateDescriptorHeap(RHIDescriptorHeapDesc& desc);

		static RHIDescriptorLayout* CreateDescriptorLayout(RHIDescriptorLayoutDesc& desc);

		static RHIDescriptorView* CreateDescriptorView(RHIDescriptorViewDesc& desc);

	};
}