#pragma once
#include "Utility/SmartPointer.h"

class IDXGISwapChain4;

namespace Alpha
{
	class D3D12Adapter;
	class D3D12CommandQueue;
	class D3D12BackBufferTexture;

	class D3D12Viewport
	{
	private:
		friend D3D12BackBufferTexture;
		ComPtr<IDXGISwapChain4> m_swapChain4;

	public:
		D3D12Viewport(D3D12Adapter* adapter, D3D12CommandQueue* queue, HWND hWnd, UINT width, UINT height);
		~D3D12Viewport();

		UINT GetWidth() const;
		UINT GetHeight() const;

		UINT GetBackBufferIndex() const;

		void Present();
	};
}