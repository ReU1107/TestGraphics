#include <d3d12.h>
#include <cassert>
#include "D3D12Resource.h"

#include "D3D12Private.h"
#include "D3D12Device.h"
#include "D3D12DescriptorHeap.h"
namespace Alpha
{
	D3D12Resource::D3D12Resource(D3D12Device* device)
		: D3D12DeviceObject(device)
		, m_shaderResourceView(nullptr)
		, m_renderTargetView(nullptr)
		, m_depthStencilView(nullptr)
		, m_unorderedAccessView(nullptr)
		, m_state(RHIResourceState::Common)
		, m_dynamic()
	{
		//UINT8* pVertexDataBegin;
		//CD3DX12_RANGE readRange(0, 0);        // We do not intend to read from this resource on the CPU.
		//ThrowIfFailed(m_vertexBuffer->Map(0, &readRange, reinterpret_cast<void**>(&pVertexDataBegin)));
		//memcpy(pVertexDataBegin, triangleVertices, sizeof(triangleVertices));
		//m_vertexBuffer->Unmap(0, nullptr);
	}

	D3D12Resource::~D3D12Resource()
	{
		delete m_depthStencilView;
		delete m_renderTargetView;
		delete m_shaderResourceView;
		delete m_unorderedAccessView;
	}

	void D3D12Resource::CreateShaderResourceView(D3D12DescriptorHeap* heap, UINT index)
	{
		m_shaderResourceView = new D3D12ResourceView(m_device, this, heap, index);
	}

	void D3D12Resource::CreateRenderTargetView(D3D12DescriptorHeap* heap, UINT index)
	{
		m_renderTargetView = new D3D12ResourceView(m_device, this, heap, index);
	}

	void D3D12Resource::CreateDepthStencilView(D3D12DescriptorHeap* heap, UINT index)
	{

	}

	void D3D12Resource::UnorderedAccessView(D3D12DescriptorHeap* heap, UINT index)
	{
	}

	D3D12ResourceView::D3D12ResourceView(D3D12Device* device, D3D12Resource* resource, D3D12DescriptorHeap* heap, UINT index)
		: D3D12DeviceObject(device)
		, m_heap(heap)
		, m_index(index)
	{
		RHIDescriptorHeapType type = heap->GetType();
		switch (type)
		{
		case RHIDescriptorHeapType::SRV:
			CreateShaderResourceView(resource->GetNativeResource());
			break;
		case RHIDescriptorHeapType::RTV:
			CreateRenderTargetView(resource->GetNativeResource());
			break;
		case RHIDescriptorHeapType::DSV:
			CreateDepthStencilView(resource->GetNativeResource());
			break;
		case RHIDescriptorHeapType::Sampler:
			break;
		default:
			break;
		}

		heap->Allocate();
	}

	D3D12ResourceView::~D3D12ResourceView()
	{
	}

	D3D12_GPU_DESCRIPTOR_HANDLE D3D12ResourceView::GetGPUSlotHandle() const
	{
		return m_heap->GetGPUSlotHandle(m_index);
	}

	D3D12_CPU_DESCRIPTOR_HANDLE D3D12ResourceView::GetCPUSlotHandle() const
	{
		return m_heap->GetCPUSlotHandle(m_index);
	}

	void D3D12ResourceView::CreateShaderResourceView(ID3D12Resource1* resource)
	{
		auto resourceDesc = resource->GetDesc();

		D3D12_SHADER_RESOURCE_VIEW_DESC nativeDesc = {};
		nativeDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		//if (raytracing)
		//{
		//	nativeDesc.ViewDimension = D3D12_SRV_DIMENSION_RAYTRACING_ACCELERATION_STRUCTURE;
		//	nativeDesc.RaytracingAccelerationStructure.Location = resource->GetGPUVirtualAddress();
		//	resource = nullptr;
		//}
		//else
		{
			// 深度値用をシェーダーリソースとして使用する場合
			switch (resourceDesc.Format)
			{
			case DXGI_FORMAT_D32_FLOAT:
				nativeDesc.Format = DXGI_FORMAT_R32_FLOAT;
				break;
			case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
				nativeDesc.Format = DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS;
				break;
			case DXGI_FORMAT_D24_UNORM_S8_UINT:
				nativeDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
				break;
			case DXGI_FORMAT_D16_UNORM:
				nativeDesc.Format = DXGI_FORMAT_R16_UNORM;
				break;
			default:
				nativeDesc.Format = resourceDesc.Format;
				break;
			}

			switch (resourceDesc.Dimension)
			{
			case D3D12_RESOURCE_DIMENSION_UNKNOWN:
				// ここに入ってきたらTextureCubeの可能性があるのかな???
				// わからんから今はとめておく
				assert(!"リソースのDimensionがおかしいです");
				break;
			case D3D12_RESOURCE_DIMENSION_BUFFER:
				nativeDesc.Format = DXGI_FORMAT_UNKNOWN;
				nativeDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
				nativeDesc.Buffer.FirstElement = 0;
				// ByteAddressBufferを使用する場合はこちら
				//if (raw)
				//{
				//	nativeDesc.Buffer.NumElements = (UINT)resourceDesc.Width / 4;
				//	nativeDesc.Buffer.StructureByteStride = 0;
				//	nativeDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_RAW;
				//	nativeDesc.Format = DXGI_FORMAT_R32_TYPELESS;
				//}
				//else
				//{
				//	nativeDesc.Buffer.NumElements = (UINT)resourceDesc.Width / stride;
				//	nativeDesc.Buffer.StructureByteStride = stride;
				//	nativeDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;
				//}
				break;
			case D3D12_RESOURCE_DIMENSION_TEXTURE1D:
				if (resourceDesc.DepthOrArraySize > 1)
				{
					nativeDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE1DARRAY;
					nativeDesc.Texture1DArray.ArraySize = resourceDesc.DepthOrArraySize;
					nativeDesc.Texture1DArray.FirstArraySlice = 0;
					nativeDesc.Texture1DArray.MipLevels = 0;
					nativeDesc.Texture1DArray.MostDetailedMip = 0;
					nativeDesc.Texture1DArray.ResourceMinLODClamp = 0;
				}
				else
				{
					nativeDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE1D;
					nativeDesc.Texture1D.MipLevels = 0;
					nativeDesc.Texture1D.MostDetailedMip = 0;
					nativeDesc.Texture1D.ResourceMinLODClamp = 0.0f;
				}

				break;
			case D3D12_RESOURCE_DIMENSION_TEXTURE2D:
				// マルチサンプリング
				if (resourceDesc.SampleDesc.Count != 1)
				{
					if (resourceDesc.DepthOrArraySize > 1)
					{
						nativeDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2DMSARRAY;
						nativeDesc.Texture2DMSArray.ArraySize = resourceDesc.DepthOrArraySize;
						nativeDesc.Texture2DMSArray.FirstArraySlice = 0;
					}
					else
					{
						nativeDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2DMS;
						//nativeDesc.Texture2DMS.UnusedField_NothingToDefine;

					}
				}
				else
				{
					if (resourceDesc.DepthOrArraySize > 1)
					{
						nativeDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2DARRAY;
						nativeDesc.Texture2DArray.ArraySize = resourceDesc.DepthOrArraySize;
						nativeDesc.Texture2DArray.FirstArraySlice = 0;
						nativeDesc.Texture2DArray.MipLevels = resourceDesc.MipLevels;
						nativeDesc.Texture2DArray.MostDetailedMip = resourceDesc.MipLevels;
						nativeDesc.Texture2DArray.ResourceMinLODClamp = 0;
					}
					else
					{
						nativeDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
						nativeDesc.Texture2D.MipLevels = resourceDesc.MipLevels;
						//nativeDesc.Texture2D.MostDetailedMip = resourceDesc.MipLevels - 1;
						nativeDesc.Texture2D.MostDetailedMip = 0;
						nativeDesc.Texture2D.ResourceMinLODClamp = 0;

					}

				}

				break;
			case D3D12_RESOURCE_DIMENSION_TEXTURE3D:
			{
				nativeDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE3D;
				nativeDesc.Texture3D.MipLevels = resourceDesc.MipLevels;
				nativeDesc.Texture3D.MostDetailedMip = resourceDesc.MipLevels - 1;
				nativeDesc.Texture3D.ResourceMinLODClamp = 0;

			}
			break;
			default:
				assert(!"リソースのDimensionがおかしいです");
				break;
			}

		}
		m_device->GetNativeDevice()->CreateShaderResourceView(resource, &nativeDesc, m_heap->GetCPUSlotHandle(m_index));
	}

	void D3D12ResourceView::CreateRenderTargetView(ID3D12Resource1* resource)
	{
		auto resourceDesc = resource->GetDesc();
		D3D12_RENDER_TARGET_VIEW_DESC renderTargetDesc = {};
		renderTargetDesc.Format = resourceDesc.Format;

		switch (resourceDesc.Dimension)
		{
		case D3D12_RESOURCE_DIMENSION_UNKNOWN:
			break;
		case D3D12_RESOURCE_DIMENSION_BUFFER:
			renderTargetDesc.Buffer.FirstElement = 0;
			renderTargetDesc.Buffer.NumElements = 0;
			break;
		case D3D12_RESOURCE_DIMENSION_TEXTURE1D:
			renderTargetDesc.Texture1D.MipSlice = 0;
			renderTargetDesc.Texture1DArray.ArraySize = 0;
			renderTargetDesc.Texture1DArray.FirstArraySlice = 0;
			renderTargetDesc.Texture1DArray.MipSlice = 0;
			break;
		case D3D12_RESOURCE_DIMENSION_TEXTURE2D:
			if (resourceDesc.SampleDesc.Count != 1)
			{
				if (resourceDesc.DepthOrArraySize > 1)
				{
					renderTargetDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2DMSARRAY;
					renderTargetDesc.Texture2DMSArray.ArraySize = resourceDesc.DepthOrArraySize;
					renderTargetDesc.Texture2DMSArray.FirstArraySlice = 0;
				}
				else
				{
					renderTargetDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2DMS;
					renderTargetDesc.Texture2DMS.UnusedField_NothingToDefine = 0;
				}
			}
			else
			{
				if (resourceDesc.DepthOrArraySize > 1)
				{
					renderTargetDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2DARRAY;
					renderTargetDesc.Texture2DArray.ArraySize = resourceDesc.DepthOrArraySize;
					renderTargetDesc.Texture2DArray.FirstArraySlice = 0;
					renderTargetDesc.Texture2DArray.MipSlice = 0;
					renderTargetDesc.Texture2DArray.PlaneSlice = 0;
				}
				else
				{
					renderTargetDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
					renderTargetDesc.Texture2D.MipSlice = 0;
					renderTargetDesc.Texture2D.PlaneSlice = 0;
				}

			}
			break;
		case D3D12_RESOURCE_DIMENSION_TEXTURE3D:
			renderTargetDesc.Texture3D.FirstWSlice = 0;
			renderTargetDesc.Texture3D.MipSlice = 0;
			renderTargetDesc.Texture3D.WSize = 0;
			break;
		default:
			break;
		}

		m_device->GetNativeDevice()->CreateRenderTargetView(resource, &renderTargetDesc, m_heap->GetCPUSlotHandle(m_index));
	}

	void D3D12ResourceView::CreateDepthStencilView(ID3D12Resource1* resource)
	{
		auto resourceDesc = resource->GetDesc();

		D3D12_DEPTH_STENCIL_VIEW_DESC depthStencilDesc = {};

		switch (resourceDesc.Dimension)
		{
		case D3D12_RESOURCE_DIMENSION_UNKNOWN:
			break;
		case D3D12_RESOURCE_DIMENSION_BUFFER:
			break;
		case D3D12_RESOURCE_DIMENSION_TEXTURE1D:
			depthStencilDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE1D;
			depthStencilDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE1DARRAY;
			depthStencilDesc.Texture1D.MipSlice = 0;
			depthStencilDesc.Texture1DArray.ArraySize = 0;
			depthStencilDesc.Texture1DArray.FirstArraySlice = 0;
			depthStencilDesc.Texture1DArray.MipSlice = 0;

			break;
		case D3D12_RESOURCE_DIMENSION_TEXTURE2D:
			// マルチサンプリング
			if (resourceDesc.SampleDesc.Count != 1)
			{
				if (resourceDesc.DepthOrArraySize > 1)
				{
					depthStencilDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2DMSARRAY;
					depthStencilDesc.Texture2DMSArray.ArraySize = resourceDesc.DepthOrArraySize;
					depthStencilDesc.Texture2DMSArray.FirstArraySlice = 0;
				}
				else
				{
					depthStencilDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2DMS;

				}
			}
			else
			{
				if (resourceDesc.DepthOrArraySize > 1)
				{
					depthStencilDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2DARRAY;
					depthStencilDesc.Texture2DArray.ArraySize = resourceDesc.DepthOrArraySize;
					depthStencilDesc.Texture2DArray.FirstArraySlice = 0;
					depthStencilDesc.Texture2DArray.MipSlice = 0;
				}
				else
				{
					depthStencilDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
					depthStencilDesc.Texture2D.MipSlice = 0;
				}

			}

			break;
		case D3D12_RESOURCE_DIMENSION_TEXTURE3D:
			break;
		default:
			break;
		}

		depthStencilDesc.Format = DXGI_FORMAT_D32_FLOAT;
		depthStencilDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
		depthStencilDesc.Flags = D3D12_DSV_FLAG_NONE;


		m_device->GetNativeDevice()->CreateDepthStencilView(resource, &depthStencilDesc, m_heap->GetCPUSlotHandle(m_index));

	}

	void D3D12ResourceView::UnorderedAccessView(ID3D12Resource1* resource)
	{
	}
}