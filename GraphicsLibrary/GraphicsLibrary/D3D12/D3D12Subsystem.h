//#pragma once
//#include <Windows.h>
//#include <string>
////#include "Utility/SmartPointer.h"
//#include "Utility/SubsystemObject.h"
//#include "D3D12Types.h"
//#include "D3D12Common.h"
//
//class D3D12Adapter;
//class D3D12Device;
//class D3D12CommandQueue;
//class D3D12Viewport;
//class D3D12CommandList;
//class D3D12Buffer;
//class D3D12Texture;
//class D3D12DescriptorHeap;
//class D3D12GraphicsPipelineState;
//class D3D12VertexShader;
//class D3D12EffectShader;
//
//class D3D12Subsystem : public SubsystemObject<D3D12Subsystem>
//{
//private:
//	D3D12Adapter* m_adapter;
//	D3D12Device* m_device;
//
//	D3D12CommandQueue* m_queue;
//
//	D3D12Viewport* m_viewport;
//
//	D3D12CommandList* m_list;
//	D3D12CommandList* m_uploadList;
//	D3D12CommandQueue* m_uploadQueue;
//
//public:
//	D3D12Subsystem();
//	~D3D12Subsystem();
//
//	bool Initialize();
//
//	void Finalize();
//
//	// バッファ作成
//	D3D12Buffer* CreateBuffer();
//
//	// テクスチャ作成
//	D3D12Texture* CreateTexture();
//
//	D3D12Texture* CreateBackBufferTexture(UINT index);
//
//	D3D12DescriptorHeap* CreateDescriptorHeap(D3D12DescriptorHeapType type, UINT num);
//
//	D3D12GraphicsPipelineState* CreateGraphicsPipelineState();
//
//	D3D12CommandList* GetImmediateCommandList() const { return m_list; }
//
//	D3D12VertexShader* CreateVertexShader();
//
//	D3D12EffectShader* CreateEffectShader(std::wstring& filePath, D3D12ShaderType type);
//
//	UINT GetCurrentIndex() const;
//
//	void UploadBegin();
//
//	void Upload(D3D12Texture* texture);
//
//	void UploadEnd();
//
//	void RenderBegin();
//
//	void RenderEnd();
//
//	void LoadWait();
//
//	ID3D12CommandQueue* GetQueue();
//
//};
