#include <d3d12.h>



#include "D3D12Device.h"
#include "D3D12Adapter.h"

#pragma comment(lib, "d3d12.lib")
#include <dxgi1_4.h>
#pragma comment(lib, "dxgi.lib")
#include <D3Dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")
namespace Alpha
{
	D3D12Device::D3D12Device(D3D12Adapter* adapter)
	{
		HRESULT hr = S_OK;

		// デバイス作成
#if _DEBUG
		ComPtr<ID3D12Debug3> debug;
		hr = D3D12GetDebugInterface(IID_PPV_ARGS(&debug));

		debug->EnableDebugLayer();
		//debug->SetEnableGPUBasedValidation(true);
#endif
		ComPtr<IDXGIAdapter1> ad;
		hr = D3D12CreateDevice(ad.Get(), D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&m_device));
		if (FAILED(hr))
		{
			MessageBox(nullptr, L"デバイスの作成に失敗しました", L"エラー", MB_OK);
		}
	}

	D3D12Device::~D3D12Device()
	{
	}

	D3D12Buffer* D3D12Device::CreateRHIBuffer() const
	{
		m_device->CreateCommittedResource1();
		//ID3D12Resource1::map
		return nullptr;
	}
}