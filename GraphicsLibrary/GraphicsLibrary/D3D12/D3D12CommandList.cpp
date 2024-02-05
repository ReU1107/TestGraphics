
#include <d3d12.h>

#include "D3D12CommandList.h"

#include "D3D12Device.h"
#include "D3D12Private.h"
#include "D3D12Resource.h"
#include "D3D12Texture.h"
#include "D3D12Buffer.h"

#include "D3D12PipelineState.h"
#include "D3D12Shader.h"

#include "D3D12DescriptorHeap.h"

#include "Utility/Utility.h"

namespace Alpha
{
	D3D12CommandList::D3D12CommandList(D3D12Device* device, RHICommandType type)
		: D3D12DeviceObject(device)
	{
		for (int i = 0; i < FrameCount; i++)
		{
			auto hr = device->GetNativeDevice()->CreateCommandAllocator(GetD3D12CommandListType(type), IID_PPV_ARGS(&m_allocators[i]));
			if (FAILED(hr))
			{
				MessageBox(nullptr, L"コマンドアロケーターの作成に失敗しました", L"エラー", MB_OK);
			}
		}

		auto hr = device->GetNativeDevice()->CreateCommandList1(0, GetD3D12CommandListType(type), D3D12_COMMAND_LIST_FLAG_NONE, IID_PPV_ARGS(&m_list));
		if (FAILED(hr))
		{
			(nullptr, L"コマンドリストの作成に失敗しました", L"エラー", MB_OK);
		}
	}

	D3D12CommandList::~D3D12CommandList()
	{
		//m_list->SetDescriptorHeaps();
		//m_list->SetGraphicsRootDescriptorTable();
	}

	void D3D12CommandList::Reset(UINT index)
	{
		ID3D12CommandAllocator* allocator = m_allocators[index].Get();
		allocator->Reset();
		m_list->Reset(allocator, nullptr);
	}

	void D3D12CommandList::TransitionResource(D3D12Resource* resource, RHIResourceState state)
	{

		D3D12_RESOURCE_BARRIER barrier = {};
		barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrier.Transition.pResource = resource->GetNativeResource();
		barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
		barrier.Transition.StateBefore = GetD3D12ResourceStates(resource->GetState());
		barrier.Transition.StateAfter = GetD3D12ResourceStates(state);

		m_list->ResourceBarrier(1, &barrier);

		resource->SetState(state);
	}

	void D3D12CommandList::SetViewport(float width, float height, float minDepth, float maxDepth)
	{
		D3D12_VIEWPORT viewport;
		viewport.TopLeftX = 0; viewport.TopLeftY = 0;
		viewport.Width = width;
		viewport.Height = height;
		viewport.MinDepth = minDepth;
		viewport.MaxDepth = maxDepth;

		m_list->RSSetViewports(1, &viewport);
	}

	void D3D12CommandList::SetScissorRect(UINT width, UINT height)
	{
		D3D12_RECT rect = {};
		rect.right = width;
		rect.bottom = height;

		m_list->RSSetScissorRects(1, &rect);
	}

	void D3D12CommandList::SetRenderTarget(D3D12Texture* renderTarget)
	{
		D3D12_CPU_DESCRIPTOR_HANDLE rtv = renderTarget->GetRenderTargetView()->GetCPUSlotHandle();

		m_list->OMSetRenderTargets(1, &rtv, false, nullptr);
	}

	void D3D12CommandList::ClearRenderTarget(D3D12Texture* renderTarget, float clearColor[4])
	{
		D3D12_CPU_DESCRIPTOR_HANDLE rtv = renderTarget->GetRenderTargetView()->GetCPUSlotHandle();

		m_list->ClearRenderTargetView(rtv, clearColor, 0, nullptr);
	}

	void D3D12CommandList::SetRootSignature(D3D12RootSignature* rootSignature)
	{
		m_list->SetGraphicsRootSignature(rootSignature->GetNativeRootSignature());
	}

	void D3D12CommandList::SetGraphicsPipeline(D3D12GraphicsPipelineState* pipeline)
	{
		m_list->SetPipelineState(pipeline->GetNativePipelineState());
	}

	void D3D12CommandList::UploadTexture(D3D12Texture* texture)
	{
		//D3D12_TEXTURE_COPY_LOCATION dest = {};
		//// コピー先
		//dest.pResource = texture->m_resource.Get();
		//// 種類
		//dest.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
		//// サブリソースのインデックス
		//dest.SubresourceIndex = 0;

		//D3D12_TEXTURE_COPY_LOCATION src = {};
		//// コピー元
		//src.pResource = texture->m_upload.Get();
		//// 種類
		//src.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
		//// オフセット
		//src.PlacedFootprint.Offset = 0;

		//D3D12_RESOURCE_DESC desc = texture->m_resource->GetDesc();

		//// リソースの情報
		//src.PlacedFootprint.Footprint.Format = desc.Format;
		//src.PlacedFootprint.Footprint.Width = static_cast<UINT>(desc.Width);
		//src.PlacedFootprint.Footprint.Height = static_cast<UINT>(desc.Height);
		//src.PlacedFootprint.Footprint.Depth = static_cast<UINT>(desc.DepthOrArraySize);
		////src.PlacedFootprint.Footprint.RowPitch = static_cast<UINT>(texture->m_rowPitch);
		//src.PlacedFootprint.Footprint.RowPitch = Alignment(texture->m_rowPitch, D3D12_TEXTURE_DATA_PITCH_ALIGNMENT);

		//m_list->CopyTextureRegion(&dest, 0, 0, 0, &src, nullptr);

		D3D12_SUBRESOURCE_DATA textureData = {};
		textureData.pData = &texture->m_data[0];
		textureData.RowPitch = texture->m_rowPitch;
		textureData.SlicePitch = texture->m_rowPitch * texture->m_height;

		UpdateSubresources(m_list.Get(), texture->GetNativeResource(), texture->GetUploadResource(), 0, 0, 1, &textureData);


		//UpdateSubresources(m_list.Get(), texture->m_resource.Get(), texture->m_upload.Get(), 0, 0, texture->m_subresources.size(), texture->m_subresources.data());
	}

	void D3D12CommandList::SetSetDescriptorHeap(D3D12DescriptorHeap* heap)
	{
		ID3D12DescriptorHeap* h = heap->GetNativeHeap();
		m_list->SetDescriptorHeaps(1, &h);
	}

	void D3D12CommandList::SetGraphicsDescriptorTable(D3D12ResourceView* view, UINT index)
	{
		m_list->SetGraphicsRootDescriptorTable(index, view->GetGPUSlotHandle());
	}

	void D3D12CommandList::SetUniformBuffer(D3D12Buffer* uniformBuffer, UINT index)
	{
		m_list->SetGraphicsRootConstantBufferView(index, uniformBuffer->GetNativeResource()->GetGPUVirtualAddress());
	}

	void D3D12CommandList::Draw(D3D12Buffer* vertexBuffer)
	{
		m_list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		D3D12_VERTEX_BUFFER_VIEW vbv = {};
		vbv.BufferLocation = vertexBuffer->GetNativeResource()->GetGPUVirtualAddress();
		vbv.StrideInBytes = vertexBuffer->GetStride();
		vbv.SizeInBytes = vertexBuffer->GetSize();
		m_list->IASetVertexBuffers(0, 1, &vbv);

		m_list->DrawInstanced(vertexBuffer->GetNum(), 1, 0, 0);


	}

	void D3D12CommandList::DrawIndex(D3D12Buffer* indexBuffer, D3D12Buffer* vertexBuffer)
	{
		m_list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		D3D12_VERTEX_BUFFER_VIEW vbv = {};
		vbv.BufferLocation = vertexBuffer->GetNativeResource()->GetGPUVirtualAddress();
		vbv.StrideInBytes = vertexBuffer->GetStride();
		vbv.SizeInBytes = vertexBuffer->GetSize();
		m_list->IASetVertexBuffers(0, 1, &vbv);

		D3D12_INDEX_BUFFER_VIEW ibv = {};
		ibv.BufferLocation = indexBuffer->GetNativeResource()->GetGPUVirtualAddress();
		ibv.Format = indexBuffer->GetStride() == sizeof(UINT) ? DXGI_FORMAT_R32_UINT : DXGI_FORMAT_R16_UINT;
		ibv.SizeInBytes = indexBuffer->GetSize();
		m_list->IASetIndexBuffer(&ibv);


		m_list->DrawIndexedInstanced(indexBuffer->GetNum(), 1, 0, 0, 0);
	}

	void D3D12CommandList::DrawIndex(D3D12Buffer* indexBuffer, D3D12Buffer* vertexBuffer[], UINT num)
	{
		m_list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		D3D12_VERTEX_BUFFER_VIEW vbv[4] = {};
		for (UINT i = 0; i < num; i++)
		{
			vbv[i].BufferLocation = vertexBuffer[i]->GetNativeResource()->GetGPUVirtualAddress();
			vbv[i].StrideInBytes = vertexBuffer[i]->GetStride();
			vbv[i].SizeInBytes = vertexBuffer[i]->GetSize();
		}

		m_list->IASetVertexBuffers(0, num, vbv);

		D3D12_INDEX_BUFFER_VIEW ibv = {};
		ibv.BufferLocation = indexBuffer->GetNativeResource()->GetGPUVirtualAddress();
		ibv.Format = indexBuffer->GetStride() == sizeof(UINT) ? DXGI_FORMAT_R32_UINT : DXGI_FORMAT_R16_UINT;
		ibv.SizeInBytes = indexBuffer->GetSize();
		m_list->IASetIndexBuffer(&ibv);


		m_list->DrawIndexedInstanced(indexBuffer->GetNum(), 1, 0, 0, 0);
	}

	void D3D12CommandList::Close()
	{
		m_list->Close();
	}
}