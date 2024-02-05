#pragma once
#include "RHI/RHIDynamic.h"
#if RHI_D3D12
#include "D3D12Resource.h"

namespace Alpha
{

	class D3D12Adapter;
	class D3D12Device;
	enum class EBufferUsage;
	enum class ERHIResourceState;

	class D3D12Dynamic : public RHIDynamic
	{
	private:
		D3D12Device* m_device;
	public:
		D3D12Dynamic();
		~D3D12Dynamic();

		virtual void Init() override;

		virtual RHIBuffer* CreateBuffer(RHIBufferDesc& desc) override;

		virtual RHITexture* CreateTexture(RHITextureDesc& desc) override;
		D3D12Buffer* CreateD3D12Buffer(class FRHICommandListImmediate* RHICmdList, uint32_t size, EBufferUsage usage, uint32_t stride, ERHIResourceState InResourceState);

		D3D12Device* GetDevice() const { return m_device; }

	};
}
#endif