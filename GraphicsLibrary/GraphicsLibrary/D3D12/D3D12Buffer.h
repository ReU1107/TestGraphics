#pragma once

#include "D3D12Resource.h"
#include "RHI/RHIResource.h"

struct D3D12_RESOURCE_DESC;

namespace Alpha
{

	class D3D12Buffer : public RHIBuffer, public D3D12Resource
	{
	public:
		D3D12Buffer()
			: RHIBuffer(0, 0, EBufferUsage::None)
			, D3D12Resource(nullptr)
		{

		}
		D3D12Buffer(D3D12Device* device, uint32_t stride, uint32_t size, EBufferUsage usage)
			: RHIBuffer(stride, size, usage)
			, D3D12Resource(device)
		{
			EnumHasFlag(usage, EBufferUsage::Dynamic);
		}


		void UploadResourceData();

		static void GetDesc(uint64_t size, EBufferUsage usage, uint32_t* alignment, D3D12_RESOURCE_DESC* desc);
	};

	//class D3D12Buffer : public D3D12Resource
	//{
	//private:
	//	UINT m_stride;
	//	UINT m_num;
	//	UINT m_size;
	//public:
	//	D3D12Buffer(D3D12Device* device);
	//	~D3D12Buffer();

	//	UINT GetStride() const { return m_stride; }
	//	UINT GetNum() const { return m_num; }
	//	UINT GetSize() const { return m_size; }

	//	void Create(UINT stride, UINT num, UINT alignment = 1, bool dynamic = true);

	//	void Upload(const void* data);

	//};
}