#pragma once
#include "D3D12Common.h"

static constexpr int FrameCount = 3;

class ID3D12CommandAllocator;
class ID3D12GraphicsCommandList5;

namespace Alpha
{
	class D3D12Device;
	class D3D12Resource;
	class D3D12Texture;
	class D3D12Buffer;

	class D3D12RootSignature;
	class D3D12GraphicsPipelineState;
	class D3D12DescriptorHeap;
	class D3D12ResourceView;

	enum class RHICommandType;
	enum class RHIResourceState;

	class D3D12CommandList : public D3D12DeviceObject
	{
	private:
		ComPtr<ID3D12CommandAllocator> m_allocators[FrameCount];
		ComPtr<ID3D12GraphicsCommandList5> m_list;


	public:
		D3D12CommandList(D3D12Device* device, RHICommandType type);
		~D3D12CommandList();

		ID3D12GraphicsCommandList5* GetNativeList() const { return m_list.Get(); }

		void Reset(UINT index);

		void TransitionResource(D3D12Resource* resource, RHIResourceState state);

		void SetViewport(float width, float height, float minDepth = 0.0f, float maxDepth = 1.0f);

		void SetScissorRect(UINT width, UINT height);

		void SetRenderTarget(D3D12Texture* renderTarget);

		void ClearRenderTarget(D3D12Texture* renderTarget, float clearColor[4]);

		void SetRootSignature(D3D12RootSignature* rootSignature);

		void SetGraphicsPipeline(D3D12GraphicsPipelineState* pipeline);

		void UploadTexture(D3D12Texture* texture);

		void SetSetDescriptorHeap(D3D12DescriptorHeap* heap);

		void SetGraphicsDescriptorTable(D3D12ResourceView* view, UINT index);
		//void SetPrimitiveTopology();

		//void SetVertexBuffer();

		void SetUniformBuffer(D3D12Buffer* uniformBuffer, UINT index);

		void Draw(D3D12Buffer* vertexBuffer);

		void DrawIndex(D3D12Buffer* indexBuffer, D3D12Buffer* vertexBuffer);
		void DrawIndex(D3D12Buffer* indexBuffer, D3D12Buffer* vertexBuffer[], UINT num);

		void Close();

	};
}