#pragma once
#include "Utility/SmartPointer.h"

class IDXGIAdapter4;
class IDXGIFactory7;

namespace Alpha
{
	class D3D12Adapter
	{
	private:
		ComPtr<IDXGIAdapter4> m_adapter4;
		ComPtr<IDXGIFactory7> m_factory7;


	public:
		D3D12Adapter();
		~D3D12Adapter();

		IDXGIAdapter4* GetNativeAdapter() { return m_adapter4.Get(); }
		IDXGIFactory7* GetNativeFactory() { return m_factory7.Get(); }

	};
}