#pragma once

//#include <d3d12.h>
//#include <dxgi1_6.h>
//#include <d3dcompiler.h>
//#include <DirectXTex.h>
//#include <d3dx12.h>
//
//#include <wrl/client.h>
//
//#pragma comment(lib,"d3d12.lib")
//#pragma comment(lib,"dxgi.lib")
//#pragma comment(lib,"dxguid.lib")
//#pragma comment(lib,"d3dcompiler.lib")
//#pragma comment(lib,"DirectXTex.lib")
//#pragma comment(lib,"DirectXTK12.lib")
//
//
//using Microsoft::WRL::ComPtr;
#include "Utility/SmartPointer.h"

#include <cstdint>

namespace Alpha
{
	class D3D12Device;

	class D3D12DeviceObject
	{
	protected:
		D3D12Device* m_device;

	public:
		D3D12DeviceObject(D3D12Device* parent)
			: m_device(parent)
		{}
		~D3D12DeviceObject() {}

		D3D12Device* GetParentDevice() const { return m_device; }

	};
}