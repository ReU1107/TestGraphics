#pragma once
#include "D3D12Common.h"
#include "D3D12Types.h"

namespace Alpha
{

	class D3D12Device;
	class D3D12CommandList;

	class D3D12CommandQueue : public D3D12DeviceObject
	{
	private:
		ComPtr<ID3D12CommandQueue> m_queue;
		ComPtr<ID3D12Fence1> m_fence;
		HANDLE m_handle;
		UINT64 m_waitValue[FrameCount];

	public:
		D3D12CommandQueue(D3D12Device* device, D3D12CommandType type = D3D12CommandType::Direct);
		~D3D12CommandQueue();

		ID3D12CommandQueue* GetNativeQueue() { return m_queue.Get(); }


		void ExecuteCommandList(D3D12CommandList* list);

		void Wait(UINT index);

	};
}