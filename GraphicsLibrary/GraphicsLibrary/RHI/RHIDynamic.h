#pragma once

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


	struct RHIBufferDesc;
	struct RHITextureDesc;
	struct RHISwapchainDesc;
	struct RHICommandBufferDesc;
	struct RHICommandQueueDesc;




	class RHIDynamic
	{
	protected:
		static RHIDynamic* s_instance;

		static void SetInstance(RHIDynamic* instance);

	public:
		static RHIDynamic* GetPtr();

		RHIDynamic();
		virtual ~RHIDynamic();

		virtual void Init() = 0;

		virtual RHISwapchain* CreateSwapchain(RHISwapchainDesc& desc) = 0;

		virtual RHIBuffer* CreateBuffer(RHIBufferDesc& desc) = 0;

		virtual RHITexture* CreateTexture(RHITextureDesc& desc) = 0;

		virtual RHICommandBuffer* CreateCommandBuffer(RHICommandBufferDesc& desc) = 0;

		virtual RHICommandQueue* CreateCommandQueue(RHICommandQueueDesc& desc) = 0;

	};

	class RHIBuilder
	{
	public:
		static RHIBuffer* CreateBuffer(RHIBufferDesc& desc)
		{
			return RHIDynamic::GetPtr()->CreateBuffer(desc);
		}

		static RHITexture* CreateTexture(RHITextureDesc& desc)
		{
			return RHIDynamic::GetPtr()->CreateTexture(desc);
		}

		static RHISwapchain* CreateSwapchain(RHISwapchainDesc& desc)
		{
			return RHIDynamic::GetPtr()->CreateSwapchain(desc);
		}
	};
}
