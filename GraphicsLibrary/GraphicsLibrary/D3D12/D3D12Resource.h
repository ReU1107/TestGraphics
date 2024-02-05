#pragma once
#include "D3D12Common.h"

struct D3D12_GPU_DESCRIPTOR_HANDLE;
struct D3D12_CPU_DESCRIPTOR_HANDLE;
class ID3D12Resource1;

namespace Alpha
{
	class D3D12DescriptorHeap;
	class D3D12Resource;
	enum class RHIResourceState;

	class D3D12ResourceView : public D3D12DeviceObject
	{
	private:
		D3D12DescriptorHeap* m_heap;
		UINT m_index;
	public:
		D3D12ResourceView(D3D12Device* device, D3D12Resource* resource, D3D12DescriptorHeap* heap, UINT index);
		~D3D12ResourceView();


		D3D12_GPU_DESCRIPTOR_HANDLE GetGPUSlotHandle() const;
		D3D12_CPU_DESCRIPTOR_HANDLE GetCPUSlotHandle() const;

	private:
		void CreateShaderResourceView(ID3D12Resource1* resource);
		void CreateRenderTargetView(ID3D12Resource1* resource);
		void CreateDepthStencilView(ID3D12Resource1* resource);
		void UnorderedAccessView(ID3D12Resource1* resource);
	};

	class D3D12Resource : public D3D12DeviceObject
	{
	public:
		ComPtr<ID3D12Resource1> m_resource;
		ComPtr<ID3D12Resource1> m_upload;
		D3D12ResourceView* m_shaderResourceView;
		D3D12ResourceView* m_renderTargetView;
		D3D12ResourceView* m_depthStencilView;
		D3D12ResourceView* m_unorderedAccessView;

		RHIResourceState m_state;
		bool m_dynamic;								// CPUからデータを転送するか true:uploadバッファを使用しない

	public:
		D3D12Resource(D3D12Device* device);
		~D3D12Resource();

		void CreateShaderResourceView(D3D12DescriptorHeap* heap, UINT index);
		void CreateRenderTargetView(D3D12DescriptorHeap* heap, UINT index);
		void CreateDepthStencilView(D3D12DescriptorHeap* heap, UINT index);
		void UnorderedAccessView(D3D12DescriptorHeap* heap, UINT index);


		ID3D12Resource1* GetNativeResource() const { return m_resource.Get(); }
		ID3D12Resource1* GetUploadResource() const { return m_upload.Get(); }

		void SetState(RHIResourceState state) { m_state = state; }

		RHIResourceState GetState() const { return m_state; }

		D3D12ResourceView* GetRenderTargetView() const { return m_renderTargetView; }
		D3D12ResourceView* GetShaderResourceView() const { return m_shaderResourceView; }

	};
}
/*
* dynamic false指定例　ComputeShaderで使用する,テクスチャとして使用する,CPUから送るデータを一度しか更新することがない場合
* falseの場合uploadバッファを使用しデータをGPUに送った後
* resourceバッファにコピーを行う
*/