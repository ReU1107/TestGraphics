#pragma once
#include "RHI/RHIDynamic.h"
#if RHI_VK
namespace Alpha
{
	class VulkanDevice;

	class VulkanDynamic : public RHIDynamic
	{
	private:
		using Base = RHIDynamic;

	public:
		VulkanDynamic();
		virtual ~VulkanDynamic();

		virtual void Init() override;

		virtual RHISwapchain* CreateSwapchain(RHISwapchainDesc& desc) override;

		virtual RHIBuffer* CreateBuffer(RHIBufferDesc& desc) override;

		virtual RHITexture* CreateTexture(RHITextureDesc& desc) override;

		virtual RHICommandBuffer* CreateCommandBuffer(RHICommandBufferDesc& desc) override;

		virtual RHICommandQueue* CreateCommandQueue(RHICommandQueueDesc& desc) override;


	private:
		VulkanDevice* mDevice;

	};

}
#endif