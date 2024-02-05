#pragma once
#include "D3D12Resource.h"

#include <string>
#include <vector>
namespace Alpha
{
	enum class RHIResourceDimension;
	enum class RHIResourceFormat;

	class D3D12Texture : public D3D12Resource
	{
	public:
		uint32_t m_width;
		uint32_t m_height;
		RHIResourceDimension m_dimension;
		RHIResourceFormat m_format;
		std::vector<D3D12_SUBRESOURCE_DATA> m_subresources;
		std::vector<UINT8> m_data;
		D3D12_PLACED_SUBRESOURCE_FOOTPRINT m_footprint;
		size_t m_rowPitch;
	public:
		D3D12Texture(D3D12Device* device);
		~D3D12Texture();

		void Create(uint32_t width, uint32_t height, RHIResourceDimension dimension, RHIResourceFormat format, RHIResourceFlags flags = D3D12ResourceFlags::None, RHIResourceState state = D3D12ResourceState::GenericRead);

		void Create(uint32_t width, uint32_t height, uint32_t pixelSize, std::vector<uint8_t>& data);

		void Load(const std::wstring& filePath);
	};

	class D3D12Viewport;

	class D3D12BackBufferTexture : public D3D12Texture
	{
	private:
		friend D3D12Viewport;

	public:

		D3D12BackBufferTexture(D3D12Device* device, D3D12Viewport* viewport, uint32_t index);
		~D3D12BackBufferTexture();

	};
}