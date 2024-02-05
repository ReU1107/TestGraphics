#pragma once
#include "D3D12Common.h"

class ID3D12DescriptorHeap;

namespace Alpha
{
	class D3D12Device;
	enum class RHIDescriptorHeapType;

	class D3D12DescriptorHeap : public D3D12DeviceObject
	{
	private:
		ComPtr<ID3D12DescriptorHeap> m_heap;
		uint32_t m_descriptorSize;
		uint32_t m_descriptorNum;
		uint32_t m_current;
		RHIDescriptorHeapType m_type;

	public:
		D3D12DescriptorHeap(D3D12Device* device, RHIDescriptorHeapType type, uint32_t num);
		~D3D12DescriptorHeap();

		D3D12_CPU_DESCRIPTOR_HANDLE GetCPUSlotHandle(uint32_t slot) const;
		D3D12_GPU_DESCRIPTOR_HANDLE GetGPUSlotHandle(uint32_t slot) const;

		RHIDescriptorHeapType GetType() const { return m_type; }

		// 
		void Allocate() { m_current++; }

		uint32_t GetCurrentIndex() const { return m_current; }

		ID3D12DescriptorHeap* GetNativeHeap() const { return m_heap.Get(); }
	};
}