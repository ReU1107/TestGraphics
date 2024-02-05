#include <d3d12.h>
#include <Third/d3dx12.h>

#include "D3D12Buffer.h"

#include "D3D12Device.h"

#include "Utility/Utility.h"

namespace Alpha
{

    D3D12Buffer::~D3D12Buffer()
    {
    }

    //void D3D12Buffer::Create(UINT stride, UINT num, UINT alignment, bool dynamic)
    //{
    //    UINT size = Alignment(stride * num, alignment);
    //    D3D12_HEAP_PROPERTIES hp = {};
    //    hp.Type = dynamic ? D3D12_HEAP_TYPE_UPLOAD : D3D12_HEAP_TYPE_DEFAULT;
    //    hp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    //    hp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
    //    hp.CreationNodeMask = 1;
    //    hp.VisibleNodeMask = 1;

    //    D3D12_RESOURCE_DESC rd = {};
    //    rd.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    //    rd.Alignment = 0;
    //    rd.Width = size;
    //    rd.Height = 1;
    //    rd.DepthOrArraySize = 1;
    //    rd.MipLevels = 1;
    //    rd.Format = DXGI_FORMAT_UNKNOWN;
    //    rd.SampleDesc.Count = 1;
    //    rd.SampleDesc.Quality = 0;
    //    rd.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    //    rd.Flags = D3D12_RESOURCE_FLAG_NONE;

    //    auto hr = m_device->GetNativeDevice()->CreateCommittedResource(
    //        &hp,
    //        D3D12_HEAP_FLAG_NONE,
    //        &rd,
    //        D3D12_RESOURCE_STATE_GENERIC_READ,
    //        nullptr,
    //        IID_PPV_ARGS(&m_resource));

    //    // データをアップロードする用のバッファ作成
    //    if (!dynamic)
    //    {
    //        m_upload;
    //    }


    //    m_stride = stride;
    //    m_num = num;
    //    m_size = size;
    //    m_dynamic = dynamic;
    //}

    //void D3D12Buffer::Upload(const void* data)
    //{
    //    UINT8* pVertexDataBegin;
    //    D3D12_RANGE readRange = {};
    //    FAILED(m_resource->Map(0, &readRange, reinterpret_cast<void**>(&pVertexDataBegin)));
    //    memcpy(pVertexDataBegin, data, m_size);
    //    m_resource->Unmap(0, nullptr);
    //}

    void D3D12Buffer::UploadResourceData()
    {
        //m_device->GetNativeDevice()->CreateCommittedResource();
    }

    void D3D12Buffer::GetDesc(uint64_t size, EBufferUsage usage, uint32_t* alignment, D3D12_RESOURCE_DESC* desc)
    {
        
        *desc = CD3DX12_RESOURCE_DESC::Buffer(size);

        if (EnumHasFlag(usage, EBufferUsage::UnorderedAccess))
        {
            (*desc).Flags |= D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
        }
        if (EnumHasFlag(usage, EBufferUsage::Uniform))
        {
            *alignment = 256;
        }

        // Structured buffers, non-ByteAddress buffers, need to be aligned to their stride to ensure that they can be addressed correctly with element based offsets.
        //alignment = (InStride > 0) && (EnumHasAnyFlags(InUsage, BUF_StructuredBuffer) || !EnumHasAnyFlags(InUsage, BUF_ByteAddressBuffer | BUF_DrawIndirect)) ? InStride : 4;

    }
}