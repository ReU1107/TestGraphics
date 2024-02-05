
#include "D3D12CommandQueue.h"

#include "D3D12Device.h"
#include "D3D12Private.h"
#include "D3D12CommandList.h"

D3D12CommandQueue::D3D12CommandQueue(D3D12Device* device, D3D12CommandType type)
	: D3D12DeviceObject(device)
	, m_waitValue()
{
	HRESULT hr = S_OK;
	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	queueDesc.Type = GetD3DCommandListType(type);

	hr = device->GetNativeDevice()->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&m_queue));

	if (FAILED(hr))
	{
		MessageBox(nullptr, L"コマンドキューの作成に失敗しました", L"エラー", MB_OK);
	}

	hr = device->GetNativeDevice()->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence));
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"コマンドフェンスの作成に失敗しました", L"エラー", MB_OK);
	}

	m_handle = CreateEvent(nullptr, FALSE, FALSE, nullptr);
}

D3D12CommandQueue::~D3D12CommandQueue()
{
	CloseHandle(m_handle);
}

void D3D12CommandQueue::ExecuteCommandList(D3D12CommandList* list)
{
	ID3D12CommandList* commandList = list->GetNativeList();
	m_queue->ExecuteCommandLists(1, &commandList);
}

void D3D12CommandQueue::Wait(UINT index)
{
	// 同期を待つ
	m_queue->Signal(m_fence.Get(), m_waitValue[index]);

	auto hr = m_fence->SetEventOnCompletion(m_waitValue[index], m_handle);
	if (FAILED(hr))
	{
		// 
	}
	WaitForSingleObjectEx(m_handle, INFINITE, false);

	m_waitValue[index]++;
}
