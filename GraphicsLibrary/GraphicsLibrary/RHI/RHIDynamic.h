#pragma once
#include "RHIDeclarations.h"

namespace Alpha
{
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
		// 
		virtual RHISwapchain* CreateSwapchain(RHISwapchainDesc& desc) = 0;
		// 
		virtual RHIBuffer* CreateBuffer(RHIBufferDesc& desc) = 0;
		// 
		virtual RHITexture* CreateTexture(RHITextureDesc& desc) = 0;
		// 
		virtual RHICommandBuffer* CreateCommandBuffer(RHICommandBufferDesc& desc) = 0;
		// 
		virtual RHICommandQueue* CreateCommandQueue(RHICommandQueueDesc& desc) = 0;
		// 
		virtual RHIShader* CreateShader(RHIShaderDesc& desc) = 0;

		virtual RHIDescriptorHeap* CreateDescriptorHeap(RHIDescriptorHeapDesc& desc) = 0;

		virtual RHIDescriptorLayout* CreateDescriptorLayout(RHIDescriptorLayoutDesc& desc) = 0;

		virtual RHIDescriptorView* CreateDescriptorView(RHIDescriptorViewDesc& desc) = 0;

	};

#define RHICreate(RHIClass)\
	auto object = new RHIClass(GetDevice());\
	object->Create(desc);\
	return object;

}
