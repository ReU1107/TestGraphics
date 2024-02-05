#include "D3D12DeviceContext.h"

#include "D3D12Device.h"
#include "D3D12Adapter.h"
#include "D3D12Viewport.h"

#include "D3D12CommandList.h"
#include "D3D12CommandQueue.h"

#include "D3D12DescriptorHeap.h"

#include "D3D12Texture.h"
#include "D3D12Buffer.h"

#include "D3D12Shader.h"
#include "D3D12PipelineState.h"


class D3D12DeviceContext::Impl
{
public:
	D3D12Adapter* m_adapter;
	D3D12Device* m_device;

	D3D12CommandList* m_list;
	D3D12CommandQueue* m_queue;

	D3D12Viewport* m_viewport;

	D3D12DescriptorHeap* m_rtHeap;

	D3D12BackBufferTexture* m_backBuffers[FrameCount];


	D3D12VertexShader* vs;
	D3D12PixelShader* ps;
	D3D12RootSignature* rs;
	D3D12GraphicsPipelineState* gps;

	D3D12Buffer* bf;
public:
	Impl();
	~Impl();

	void Startup(HWND hWnd, UINT width, UINT height);


	void Render(float color[4]);

};


D3D12DeviceContext::Impl::Impl()
	: m_adapter(nullptr)
	, m_device(nullptr)
	, m_list(nullptr)
	, m_queue(nullptr)
	, m_viewport(nullptr)
	, m_rtHeap(nullptr)
	, vs(nullptr)
	, ps(nullptr)
	, rs(nullptr)
	, gps(nullptr)
	, bf(nullptr)
	, m_backBuffers()
{
}

D3D12DeviceContext::Impl::~Impl()
{
	m_queue->Wait(m_viewport->GetBackBufferIndex());

	for (UINT i = 0; i < FrameCount; i++)
	{
		delete m_backBuffers[i];
	}
	delete m_rtHeap;

	delete m_list;

	delete m_queue;
	delete m_viewport;

	delete m_device;
	delete m_adapter;
}

void D3D12DeviceContext::Impl::Startup(HWND hWnd, UINT width, UINT height)
{
	m_adapter = new D3D12Adapter();
	m_device = new D3D12Device(m_adapter);
	m_queue = new D3D12CommandQueue(m_device);
	m_viewport = new D3D12Viewport(m_adapter, m_queue, hWnd, width, height);

	m_list = new D3D12CommandList(m_device);

	m_rtHeap = new D3D12DescriptorHeap(m_device, D3D12DescriptorHeapType::RTV, FrameCount);

	for (UINT i = 0; i < FrameCount; i++)
	{
		m_backBuffers[i] = new D3D12BackBufferTexture(m_device, m_viewport, i);
		m_backBuffers[i]->CreateRenderTargetView(m_rtHeap, i);
	}

	//std::wstring a = L"C:/Users\/wner/source/repos/ModelViewer/GraphicsLibrary/VertexShader.hlsl";
	//vs = new D3D12VertexShader(m_device, a);
	//a = L"C:/Users/owner/source/repos/ModelViewer/GraphicsLibrary/PixelShader.hlsl";
	//ps = new D3D12PixelShader(m_device, a);

	//rs = new D3D12RootSignature(m_device);
	//gps = new D3D12GraphicsPipelineState(m_device);

	//gps->CreateByFX(vs, ps, rs);

	//bf = new D3D12Buffer(m_device);

}

void D3D12DeviceContext::Impl::Render(float color[4])
{
	UINT targetIndex = m_viewport->GetBackBufferIndex();

	D3D12BackBufferTexture* currentBackBuffer = m_backBuffers[targetIndex];

	m_list->Reset(targetIndex);

	m_list->SetGraphicsPipeline(gps);
	m_list->SetRootSignature(rs);

	m_list->TransitionResource(currentBackBuffer, D3D12ResourceState::RenderTarget);

	m_list->SetViewport((float)m_viewport->GetWidth(), (float)m_viewport->GetHeight());
	m_list->SetScissorRect(m_viewport->GetWidth(), m_viewport->GetHeight());

	m_list->SetRenderTarget(currentBackBuffer);

	m_list->ClearRenderTarget(currentBackBuffer, color);

	m_list->Draw(bf);

	m_list->TransitionResource(currentBackBuffer, D3D12ResourceState::Present);

	m_list->Close();


	// 実際に実行させる
	m_queue->ExecuteCommandList(m_list);

	m_viewport->Present();

	m_queue->Wait(m_viewport->GetBackBufferIndex());

}


D3D12DeviceContext::D3D12DeviceContext()
	: m_impl(new Impl())
{
}

D3D12DeviceContext::~D3D12DeviceContext()
{
	delete m_impl;

}

void D3D12DeviceContext::Startup(HWND hWnd, UINT width, UINT height)
{
	m_impl->Startup(hWnd, width, height);
}

void D3D12DeviceContext::Render(float color[4])
{
	m_impl->Render(color);

}

/*
予定
class RenderCommand
{

}

class RenderCommands
{
	enum // 実行タイミング
	RenderCommand[]
}

Render関数の中で実行タイミングに伴った場所で処理を行う

*/