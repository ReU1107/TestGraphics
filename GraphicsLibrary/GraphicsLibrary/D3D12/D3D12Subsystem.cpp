//
//#include "D3D12Subsystem.h"
//
//#include "WindowsSubsystem.h"
//
//#include "D3D12Adapter.h"
//#include "D3D12Device.h"
//#include "D3D12Viewport.h"
//#include "D3D12CommandList.h"
//#include "D3D12CommandQueue.h"
//
//
//#include "D3D12Buffer.h"
//#include "D3D12Texture.h"
//#include "D3D12DescriptorHeap.h"
//#include "D3D12Shader.h"
//#include "D3D12PipelineState.h"
//
//using namespace std;
//
//D3D12Subsystem::D3D12Subsystem()
//	: m_adapter(nullptr)
//	, m_device(nullptr)
//	, m_queue(nullptr)
//	, m_viewport(nullptr)
//	, m_list(nullptr)
//	, m_uploadList(nullptr)
//	, m_uploadQueue(nullptr)
//{
//
//	//MessageBox(nullptr, L"コンストラクタが呼ばれました", L"D3D12Subsystem", MB_OK);
//
//}
//
//D3D12Subsystem::~D3D12Subsystem()
//{
//	delete m_list;
//	delete m_viewport;
//	delete m_queue;
//	delete m_device;
//	delete m_adapter;
//}
//
//bool D3D12Subsystem::Initialize()
//{
//	HWND hWnd = WindowsSubsystem::Get().GetHandle();
//	UINT width = WindowsSubsystem::Get().GetWidth();
//	UINT height = WindowsSubsystem::Get().GetHeight();
//	
//		
//	m_adapter = new D3D12Adapter();
//	//MessageBox(nullptr, L"アダプター作成終了", L"", MB_OK);
//
//	m_device = new D3D12Device(m_adapter);
//	//MessageBox(nullptr, L"デバイス作成終了", L"", MB_OK);
//
//	m_queue = new D3D12CommandQueue(m_device);
//	//MessageBox(nullptr, L"イミディエイトコマンドキュー作成終了", L"", MB_OK);
//
//	m_viewport = new D3D12Viewport(m_adapter, m_queue, hWnd, width, height);
//	//MessageBox(nullptr, L"ビューポート作成終了", L"", MB_OK);
//
//	m_list = new D3D12CommandList(m_device);
//	//MessageBox(nullptr, L"イミディエイトコマンドリスト作成終了", L"", MB_OK);
//
//	m_uploadQueue = new D3D12CommandQueue(m_device);
//	//MessageBox(nullptr, L"アップロードコマンドキュー作成終了", L"", MB_OK);
//
//	m_uploadList = new D3D12CommandList(m_device);
//	//MessageBox(nullptr, L"アップロードコマンドリスト作成終了", L"", MB_OK);
//
//	return true;
//}
//
//void D3D12Subsystem::Finalize()
//{
//}
//
//D3D12Buffer* D3D12Subsystem::CreateBuffer()
//{
//	return new D3D12Buffer(m_device);
//}
//
//D3D12Texture* D3D12Subsystem::CreateTexture()
//{
//	return new D3D12Texture(m_device);
//}
//
//D3D12Texture* D3D12Subsystem::CreateBackBufferTexture(UINT index)
//{
//	return new D3D12BackBufferTexture(m_device, m_viewport, index);
//}
//
//D3D12DescriptorHeap* D3D12Subsystem::CreateDescriptorHeap(D3D12DescriptorHeapType type, UINT num)
//{
//	return new D3D12DescriptorHeap(m_device, type, num);
//}
//
//D3D12GraphicsPipelineState* D3D12Subsystem::CreateGraphicsPipelineState()
//{
//	return new D3D12GraphicsPipelineState(m_device);
//}
//
//D3D12VertexShader* D3D12Subsystem::CreateVertexShader()
//{
//	std::wstring a = L"C:/Users/owner/source/repos/ModelViewer/GraphicsLibrary/TestShader.hlsl";
//
//	return new D3D12VertexShader(m_device, a);
//}
//
//D3D12EffectShader* D3D12Subsystem::CreateEffectShader(std::wstring& filePath, D3D12ShaderType type)
//{
//	return new D3D12EffectShader(m_device, filePath, type);
//}
//
//UINT D3D12Subsystem::GetCurrentIndex() const
//{
//	return m_viewport->GetBackBufferIndex();
//}
//
//void D3D12Subsystem::UploadBegin()
//{
//	m_uploadList->Reset(0);
//}
//
//void D3D12Subsystem::Upload(D3D12Texture* texture)
//{
//	m_uploadList->UploadTexture(texture);
//	m_uploadList->TransitionResource(texture, D3D12ResourceState::PixelShaderResource);
//
//}
//
//void D3D12Subsystem::UploadEnd()
//{
//	m_uploadList->Close();
//	m_uploadQueue->ExecuteCommandList(m_uploadList);
//
//	m_uploadQueue->Wait(0);
//}
//
//void D3D12Subsystem::RenderBegin()
//{
//	UINT targetIndex = m_viewport->GetBackBufferIndex();
//	m_list->Reset(targetIndex);
//
//
//
//	m_list->SetViewport((float)m_viewport->GetWidth(), (float)m_viewport->GetHeight());
//	m_list->SetScissorRect(m_viewport->GetWidth(), m_viewport->GetHeight());
//
//}
//
//void D3D12Subsystem::RenderEnd()
//{
//	m_list->Close();
//
//
//	// 実際に実行させる
//	m_queue->ExecuteCommandList(m_list);
//
//	m_viewport->Present();
//
//	m_queue->Wait(m_viewport->GetBackBufferIndex());
//}
//
//void D3D12Subsystem::LoadWait()
//{
//	m_list->Close();
//
//
//	// 実際に実行させる
//	m_queue->ExecuteCommandList(m_list);
//
//	m_queue->Wait(m_viewport->GetBackBufferIndex());
//}
//
//ID3D12CommandQueue* D3D12Subsystem::GetQueue()
//{
//	return m_queue->GetNativeQueue();
//}
