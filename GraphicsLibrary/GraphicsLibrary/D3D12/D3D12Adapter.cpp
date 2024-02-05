#include <dxgi1_6.h>
#include "D3D12Adapter.h"

namespace Alpha
{

	D3D12Adapter::D3D12Adapter()
		: m_adapter4(nullptr)
		, m_factory7(nullptr)
	{
		HRESULT hr = S_OK;

		UINT flag = 0;
#if _DEBUG
		flag |= DXGI_CREATE_FACTORY_DEBUG;
#endif
		hr = CreateDXGIFactory2(flag, IID_PPV_ARGS(&m_factory7));

		if (FAILED(hr))
		{
			MessageBox(nullptr, L"ファクトリー作成に失敗しました", L"エラー", MB_OK);
		}


		bool performance = true;
		DXGI_GPU_PREFERENCE per = DXGI_GPU_PREFERENCE_UNSPECIFIED;

		ComPtr<IDXGIAdapter4> adapter = nullptr;
		per = performance ? DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE : DXGI_GPU_PREFERENCE_MINIMUM_POWER;

		hr = m_factory7->EnumAdapterByGpuPreference(0, per, IID_PPV_ARGS(&m_adapter4));

		if (FAILED(hr))
		{
			MessageBox(nullptr, L"アダプター作成に失敗しました", L"エラー", MB_OK);
		}
	}

	D3D12Adapter::~D3D12Adapter()
	{
	}
}