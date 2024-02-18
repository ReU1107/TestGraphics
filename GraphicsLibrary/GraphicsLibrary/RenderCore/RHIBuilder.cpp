#include "RHIBuilder.h"
#include "RHI/RHIDynamic.h"

namespace Alpha
{
#define CallCreateFunc(Func)\
	return RHIDynamic::GetPtr()->Func##(desc)

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

	RHIDescriptorHeap* RHIBuilder::CreateDescriptorHeap(RHIDescriptorHeapDesc& desc)
	{
		CallCreateFunc(CreateDescriptorHeap);
	}

	RHIDescriptorLayout* RHIBuilder::CreateDescriptorLayout(RHIDescriptorLayoutDesc& desc)
	{
		CallCreateFunc(CreateDescriptorLayout);
	}

	RHIDescriptorView* RHIBuilder::CreateDescriptorView(RHIDescriptorViewDesc& desc)
	{
		CallCreateFunc(CreateDescriptorView);
	}

}