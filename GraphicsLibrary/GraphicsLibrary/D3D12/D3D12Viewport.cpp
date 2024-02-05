#include <dxgi1_6.h>
#include "D3D12Viewport.h"

#include "D3D12Adapter.h"
#include "D3D12CommandQueue.h"
namespace Alpha
{
	D3D12Viewport::D3D12Viewport(D3D12Adapter* adapter, D3D12CommandQueue* queue, HWND hWnd, UINT width, UINT height)
	{

		DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
		swapChainDesc.BufferCount = FrameCount;
		swapChainDesc.Width = width;
		swapChainDesc.Height = height;
		swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		swapChainDesc.SampleDesc.Count = 1;

		ComPtr<IDXGISwapChain1> swapChain;
		auto hr = adapter->GetNativeFactory()->CreateSwapChainForHwnd(
			queue->GetNativeQueue(),
			hWnd,
			&swapChainDesc,
			nullptr,
			nullptr,
			&swapChain
		);

		if (FAILED(hr))
		{
			MessageBox(nullptr, L"スワップチェインの作成に失敗しました", L"エラー", MB_OK);
		}

		hr = swapChain.As(&m_swapChain4);
		if (FAILED(hr))
		{
			MessageBox(nullptr, L"スワップチェインの変換に失敗しました", L"エラー", MB_OK);
		}
	}

	D3D12Viewport::~D3D12Viewport()
	{
	}

	UINT D3D12Viewport::GetWidth() const
	{
		DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};

		m_swapChain4->GetDesc1(&swapChainDesc);
		return swapChainDesc.Width;
	}

	UINT D3D12Viewport::GetHeight() const
	{
		DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};

		m_swapChain4->GetDesc1(&swapChainDesc);
		return swapChainDesc.Height;
	}

	UINT D3D12Viewport::GetBackBufferIndex() const
	{
		return m_swapChain4->GetCurrentBackBufferIndex();
	}

	void D3D12Viewport::Present()
	{
		m_swapChain4->Present(1, 0);
	}
}
