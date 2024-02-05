#include <d3d12.h>
#include "D3D12DescriptorHeap.h"

#include "D3D12Device.h"
#include "D3D12Private.h"

#include "RHI/RHITypes.h"

#include "Utility/Utility.h"

namespace Alpha
{
	D3D12DescriptorHeap::D3D12DescriptorHeap(D3D12Device* device, RHIDescriptorHeapType type, uint32_t num)
		: D3D12DeviceObject(device)
		, m_descriptorNum(num)
		, m_descriptorSize()
		, m_type(type)
		, m_current()
	{
		D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
		heapDesc.NumDescriptors = num;
		heapDesc.Type = GetD3D12DescriptorHeapType(type);
		heapDesc.Flags = Compare(type, RHIDescriptorHeapType::SRV, D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE, D3D12_DESCRIPTOR_HEAP_FLAG_NONE);
		device->GetNativeDevice()->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&m_heap));

		m_descriptorSize = device->GetNativeDevice()->GetDescriptorHandleIncrementSize(GetD3D12DescriptorHeapType(type));
	}

	D3D12DescriptorHeap::~D3D12DescriptorHeap()
	{

	}

	D3D12_CPU_DESCRIPTOR_HANDLE D3D12DescriptorHeap::GetCPUSlotHandle(uint32_t slot) const
	{
		D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = m_heap->GetCPUDescriptorHandleForHeapStart();
		// タイプに基づいたサイズ取得
		UINT64 stride = (UINT64)m_descriptorSize * slot;
		cpuHandle.ptr += stride;

		return cpuHandle;
	}

	D3D12_GPU_DESCRIPTOR_HANDLE D3D12DescriptorHeap::GetGPUSlotHandle(uint32_t slot) const
	{
		D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle = m_heap->GetGPUDescriptorHandleForHeapStart();
		UINT64 stride = (UINT64)m_descriptorSize * slot;
		gpuHandle.ptr += stride;
		return gpuHandle;
	}

}