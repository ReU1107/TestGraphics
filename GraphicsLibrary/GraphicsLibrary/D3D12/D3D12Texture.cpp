#include <d3d12.h>
#include <d3dx12.h>
#include <WICTextureLoader.h>
#include <ResourceUploadBatch.h>

#include "D3D12Texture.h"

#include "D3D12Device.h"
#include "D3D12Viewport.h"
#include "D3D12Private.h"
#include "Utility/Utility.h"

#include "D3D12Subsystem.h"

namespace Alpha
{

	D3D12Texture::D3D12Texture(D3D12Device* device)
		: D3D12Resource(device)
		, m_width()
		, m_height()
		, m_dimension()
		, m_format()
	{
		m_dynamic = false;
	}

	D3D12Texture::~D3D12Texture()
	{

	}

	void D3D12Texture::Create(UINT width, UINT height, D3D12ResourceDimension dimension, D3D12ResourceFormat format, D3D12ResourceFlags flags, D3D12ResourceState state)
	{
		D3D12_RESOURCE_DESC nativeDesc = {};
		nativeDesc.Dimension = GetD3DResourceDimension(dimension);
		nativeDesc.Alignment = 0;
		nativeDesc.Width = width;
		nativeDesc.Height = height;
		nativeDesc.DepthOrArraySize = 1;		// TODO: 3d,array‚ðŽg—p‚·‚éê‡‚Í•ÏX‚·‚é
		nativeDesc.MipLevels = 1;
		nativeDesc.Format = GetDXGIFormat(format);
		nativeDesc.SampleDesc.Count = 1;
		nativeDesc.SampleDesc.Quality = 0;
		nativeDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
		nativeDesc.Flags = GetD3D12ResourceFlags(flags);

		D3D12_HEAP_PROPERTIES prop = CD3D3D12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);

		auto hr = m_device->GetNativeDevice()->CreateCommittedResource(&prop, D3D12_HEAP_FLAG_NONE, &nativeDesc, D3D12_RESOURCE_STATE_COPY_DEST, nullptr, IID_PPV_ARGS(&m_resource));


		const UINT64 uploadBufferSize = GetRequiredIntermediateSize(m_resource.Get(), 0, 1);

		prop = CD3D3D12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
		nativeDesc = CD3D3D12_RESOURCE_DESC::Buffer(uploadBufferSize);
		hr = m_device->GetNativeDevice()->CreateCommittedResource(&prop, D3D12_HEAP_FLAG_NONE, &nativeDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&m_upload));

		m_width = width;
		m_height = height;
		m_dimension = dimension;
		m_format = format;
		m_state = state;
	}

	void D3D12Texture::Create(UINT width, UINT height, UINT pixelSize, std::vector<UINT8>& data)
	{
		D3D12_RESOURCE_DESC textureDesc = {};
		textureDesc.MipLevels = 1;
		textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		textureDesc.Width = width;
		textureDesc.Height = height;
		textureDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
		textureDesc.DepthOrArraySize = 1;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.SampleDesc.Quality = 0;
		textureDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;


		D3D12_HEAP_PROPERTIES hp = CD3D3D12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
		auto hr = m_device->GetNativeDevice()->CreateCommittedResource(
			&hp,
			D3D12_HEAP_FLAG_NONE,
			&textureDesc,
			D3D12_RESOURCE_STATE_COPY_DEST,
			nullptr,
			IID_PPV_ARGS(&m_resource));

		const UINT64 uploadBufferSize = GetRequiredIntermediateSize(m_resource.Get(), 0, 1);

		D3D12_HEAP_PROPERTIES h = CD3D3D12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
		D3D12_RESOURCE_DESC d = CD3D3D12_RESOURCE_DESC::Buffer(uploadBufferSize);
		// Create the GPU upload buffer.
		hr = m_device->GetNativeDevice()->CreateCommittedResource(
			&h,
			D3D12_HEAP_FLAG_NONE,
			&d,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&m_upload));

		D3D12_SUBRESOURCE_DATA textureData = {};
		textureData.pData = &data[0];
		textureData.RowPitch = width * pixelSize;
		textureData.SlicePitch = textureData.RowPitch * height;

		m_state = D3D12ResourceState::CopyDestination;
		m_data = data;
		m_rowPitch = width * pixelSize;
		m_width = width;
		m_height = height;
		//UpdateSubresources(m_commandList.Get(), m_resource.Get(), textureUploadHeap.Get(), 0, 0, 1, &textureData);
		//m_commandList->ResourceBarrier(1, &CD3D3D12_RESOURCE_BARRIER::Transition(m_texture.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE));

	}

	void D3D12Texture::Load(const std::wstring& filePath)
	{
		ComPtr<ID3D12Resource> tex;

		DirectX::ResourceUploadBatch resourceUpload(m_device->GetNativeDevice());

		resourceUpload.Begin();

		auto hr = CreateWICTextureFromFile(m_device->GetNativeDevice(), resourceUpload, filePath.c_str(), tex.ReleaseAndGetAddressOf(), true);
		// Upload the resources to the GPU.
		auto uploadResourcesFinished = resourceUpload.End(D3D12Subsystem::Get().GetQueue());

		// Wait for the upload thread to terminate
		uploadResourcesFinished.wait();


		tex.As(&m_resource);

		////L"Assets/test_image.png"
		//DirectX::TexMetadata metadata = {};
		//DirectX::ScratchImage image = {}; 
		//auto hr = DirectX::LoadFromWICFile(filePath.c_str(), DirectX::WIC_FLAGS_NONE, &metadata, image);


		//ID3D12Resource* pResource = nullptr;
		//hr = DirectX::CreateTexture(m_device->GetNativeDevice(), image.GetMetadata(), &pResource);

		//std::vector<D3D12_SUBRESOURCE_DATA> subresources;
		//hr = DirectX::PrepareUpload(m_device->GetNativeDevice(), image.GetImages(), image.GetImageCount(), metadata,subresources);

		//// upload is implemented by application developer. Here's one solution using <d3dx12.h>
		//const UINT64 uploadBufferSize = GetRequiredIntermediateSize(pResource,	0, static_cast<unsigned int>(subresources.size()));

		//auto p = CD3D3D12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
		//auto desc = CD3D3D12_RESOURCE_DESC::Buffer(uploadBufferSize);

		//ComPtr<ID3D12Resource> textureUploadHeap;
		//hr = m_device->GetNativeDevice()->CreateCommittedResource(
		//	&p,
		//	D3D12_HEAP_FLAG_NONE,
		//	&desc,
		//	D3D12_RESOURCE_STATE_GENERIC_READ,
		//	nullptr,
		//	IID_PPV_ARGS(textureUploadHeap.GetAddressOf()));


		//pResource->QueryInterface(IID_PPV_ARGS(&m_resource));
		//textureUploadHeap.As(&m_upload);
		//m_subresources = subresources;
		////m_rowPitch = pImage->rowPitch;
		//SetState(D3D12ResourceState::CopyDestination);






		//std::vector<D3D12_SUBRESOURCE_DATA> subresources;
		//hr = PrepareUpload(m_device->GetNativeDevice(), image.GetImages(), image.GetImageCount(), metadata, subresources);


		//D3D12_RESOURCE_DESC desc = {};
		//desc.Dimension = static_cast<D3D12_RESOURCE_DIMENSION>(metadata.dimension);
		//desc.Width = static_cast<UINT64>(metadata.width);
		//desc.Height = static_cast<UINT>(metadata.height);
		//desc.DepthOrArraySize = static_cast<UINT16>(metadata.arraySize);
		//desc.MipLevels = static_cast<UINT16>(metadata.mipLevels);
		//desc.SampleDesc.Count = 1;
		//desc.SampleDesc.Quality = 0;
		//desc.Format = metadata.format;
		//desc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;

		//ComPtr<ID3D12Resource1> pResource = nullptr;
		//D3D12_HEAP_PROPERTIES heap = CD3D3D12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
		//hr = m_device->GetNativeDevice()->CreateCommittedResource(
		//	&heap,
		//	D3D12_HEAP_FLAG_NONE,
		//	&desc,
		//	D3D12_RESOURCE_STATE_COPY_DEST,
		//	nullptr,
		//	IID_PPV_ARGS(&pResource));

		//D3D12_PLACED_SUBRESOURCE_FOOTPRINT footprint = {};
		//UINT64 totalBytes = GetRequiredIntermediateSize(pResource.Get(), 0, subresources.size());

		//desc = CD3D3D12_RESOURCE_DESC::Buffer(totalBytes);
		//heap = CD3D3D12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
		//ComPtr<ID3D12Resource1> textureUploadHeap;
		//hr = m_device->GetNativeDevice()->CreateCommittedResource(
		//	&heap,
		//	D3D12_HEAP_FLAG_NONE,
		//	&desc,
		//	D3D12_RESOURCE_STATE_GENERIC_READ,
		//	nullptr,
		//	IID_PPV_ARGS(&textureUploadHeap));


	}

	D3D12BackBufferTexture::D3D12BackBufferTexture(D3D12Device* device, D3D12Viewport* viewport, UINT index)
		: D3D12Texture(device)
	{
		viewport->m_swapChain4->GetBuffer(index, IID_PPV_ARGS(&m_resource));

	}

	D3D12BackBufferTexture::~D3D12BackBufferTexture()
	{
	}

}

/*
* https://alphakaz.hatenablog.com/entry/2022/10/05/001816
*/

/*
* 
	hr = DirectX::CreateTexture(m_device->GetNativeDevice(), metadata, &pResource);

	std::vector<D3D12_SUBRESOURCE_DATA> subresources;
	hr = PrepareUpload(m_device->GetNativeDevice(), image.GetImages(), image.GetImageCount(), metadata,subresources);

	// upload is implemented by application developer. Here's one solution using <d3dx12.h>
	const UINT64 uploadBufferSize = GetRequiredIntermediateSize(pResource.Get(),
			0, static_cast<unsigned int>(subresources.size()));

	desc = pResource->GetDesc();

	D3D12_PLACED_SUBRESOURCE_FOOTPRINT footprint = {};
	uint64_t totalBytes = 0;
	uint32_t rowCount = 0;
	uint64_t byte = 0;
	m_device->GetNativeDevice()->GetCopyableFootprints(&desc, 0, 1, 0, &footprint, &rowCount, &byte, &totalBytes);

	desc = CD3D3D12_RESOURCE_DESC::Buffer(uploadBufferSize);


	uint8_t* mapData = nullptr;
	if (FAILED(textureUploadHeap->Map(0, nullptr, (void**)&mapData)))
	{
	}

	auto images = image.GetImages();
	uint32_t imageCount = (uint32_t)image.GetImageCount();
	for (uint32_t i = 0; i < imageCount; ++i)
	{
		auto& image = images[i];
		for (uint32_t j = 0; j < rowCount; ++j)
		{
			auto destination = mapData + footprint.Offset + (footprint.Footprint.RowPitch * j);
			auto source = image.pixels + (image.rowPitch * j);
			memcpy(destination, source, image.rowPitch);
		}
	}

	textureUploadHeap->Unmap(0, nullptr);
	m_footprint = footprint;
*/

/*
* 
	D3D12_RESOURCE_DESC textureDesc = {};
	textureDesc.MipLevels = 1;
	textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	textureDesc.Width = static_cast<UINT>(metadata.width);
	textureDesc.Height = static_cast<UINT>(metadata.height);
	textureDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
	textureDesc.DepthOrArraySize = 1;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	auto textureHeapProp = CD3D3D12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	FAILED(m_device->GetNativeDevice()->CreateCommittedResource(
		&textureHeapProp,
		D3D12_HEAP_FLAG_NONE,
		&textureDesc,
		D3D12_RESOURCE_STATE_COPY_DEST,
		nullptr,
		IID_PPV_ARGS(&m_resource)));


	D3D12_RESOURCE_DESC desc = m_resource->GetDesc();

	D3D12_PLACED_SUBRESOURCE_FOOTPRINT footprint = {};
	uint64_t totalBytes = 0;
	uint32_t rowCount = 0;
	uint64_t byte = 0;
	m_device->GetNativeDevice()->GetCopyableFootprints(&desc, 0, 1, 0, &footprint, &rowCount, &byte, &totalBytes);

	const UINT64 textureBufferSize = totalBytes;
	auto textureUploadHeapProp = CD3D3D12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	auto textureUploadDesc = CD3D3D12_RESOURCE_DESC::Buffer(textureBufferSize);
	FAILED(m_device->GetNativeDevice()->CreateCommittedResource(
		&textureUploadHeapProp,
		D3D12_HEAP_FLAG_NONE,
		&textureUploadDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&m_upload)));



*/