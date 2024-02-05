#pragma once
#include "Utility/SmartPointer.h"

class ID3D12Device7;

namespace Alpha
{
	class D3D12Adapter;
	class D3D12Buffer;

	class D3D12Device
	{
	private:
		ComPtr<ID3D12Device7> m_device;

	public:
		D3D12Device(D3D12Adapter* adapter);
		~D3D12Device();


		ID3D12Device7* GetNativeDevice() const { return m_device.Get(); }

		D3D12Buffer* CreateRHIBuffer() const;
	};
}