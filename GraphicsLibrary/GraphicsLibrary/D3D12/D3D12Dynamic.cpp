#include "D3D12Dynamic.h"

#if RHI_D3D12
#include <d3d12.h>

#include "D3D12Buffer.h"
#include "D3D12Texture.h"
#include "D3D12Device.h"
#include "D3D12Adapter.h"

namespace Alpha
{

	D3D12Dynamic::D3D12Dynamic()
	{
		RHIDynamic::s_instance = this;
	}

	D3D12Dynamic::~D3D12Dynamic()
	{
		RHIDynamic::s_instance = nullptr;
	}

	void D3D12Dynamic::Init()
	{
	}

	RHIBuffer* D3D12Dynamic::CreateBuffer(RHIBufferDesc& desc)
	{
		return nullptr;
	}

	RHITexture* D3D12Dynamic::CreateTexture(RHITextureDesc& desc)
	{
		return nullptr;
	}

	D3D12Buffer* D3D12Dynamic::CreateD3D12Buffer(FRHICommandListImmediate* RHICmdList, uint32_t size, EBufferUsage usage, uint32_t stride, ERHIResourceState InResourceState)
	{
		GetDevice();

		D3D12_RESOURCE_DESC desc = {};
		uint32_t alignment = 0;
		D3D12Buffer::GetDesc(size, usage, &alignment, &desc);

		const bool bIsDynamic = EnumHasFlag(usage, EBufferUsage::Dynamic);
		D3D12_HEAP_TYPE HeapType = bIsDynamic ? D3D12_HEAP_TYPE_UPLOAD : D3D12_HEAP_TYPE_DEFAULT;

		GetDevice()->CreateRHIBuffer() :

			D3D12Buffer * buffer = new D3D12Buffer();
		ID3D12Device8* ll;
		D3D12_STATE_OBJECT_DESC::Type
		ll->CreateStateObject()
		D3D12_RASTERIZER_DESC;
		D3D12_SAMPLER_DESC::
		return nullptr;
	}
}
#endif