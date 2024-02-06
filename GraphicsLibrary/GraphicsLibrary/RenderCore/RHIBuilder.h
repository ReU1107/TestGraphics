#pragma once
#include "RHI/RHIDefinitions.h"

namespace Alpha
{
	class RHIBuffer;
	class RHICommandList;
	class RHIView;
	class RHITexture;
	class RHISwapchain;
	class RHICommandBuffer;
	class RHICommandQueue;
	class RHIBuffer;


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

	};
}