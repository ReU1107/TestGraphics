#include "RHIBuilder.h"
#include "RHI/RHIDynamic.h"

namespace Alpha
{
	RHIBuffer* RHIBuilder::CreateBuffer(RHIBufferDesc& desc)
	{
		return RHIDynamic::GetPtr()->CreateBuffer(desc);
	}

	RHITexture* RHIBuilder::CreateTexture(RHITextureDesc& desc)
	{
		return RHIDynamic::GetPtr()->CreateTexture(desc);
	}

	RHISwapchain* RHIBuilder::CreateSwapchain(RHISwapchainDesc& desc)
	{
		return RHIDynamic::GetPtr()->CreateSwapchain(desc);
	}

	RHICommandBuffer* RHIBuilder::CreateCommandBuffer(RHICommandBufferDesc& desc)
	{
		return RHIDynamic::GetPtr()->CreateCommandBuffer(desc);
	}

	RHICommandQueue* RHIBuilder::CreateCommandQueue(RHICommandQueueDesc& desc)
	{
		return RHIDynamic::GetPtr()->CreateCommandQueue(desc);
	}

}