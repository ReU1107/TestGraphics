#pragma once
#include <cstdint>
#include "RHITypes.h"
namespace Alpha
{


	class RHIResource
	{
	private:
		ERHIResourceType m_type;
		ERHIResourceState m_state;
	public:
		RHIResource(ERHIResourceType type)
			: m_type(type)
			, m_state()
		{

		}
		virtual ~RHIResource() {}

		// タイプ取得
		ERHIResourceType GetType() const { return m_type; }
		// 状態取得
		ERHIResourceState GetState() const { return m_state; }
	};

	class RHIBuffer : public RHIResource
	{
	private:
		uint32_t mStride;
		uint32_t mSize;
		EBufferUsage m_usage;
	public:
		RHIBuffer(uint32_t stride, uint32_t size, EBufferUsage usage)
			: RHIResource(ERHIResourceType::Buffer)
			, mStride(stride)
			, mSize(size)
			, m_usage(usage)
		{

		}
		virtual ~RHIBuffer() {}

		// バッファストライド取得
		uint32_t GetStride() const { return mStride; }
		// サイズ取得
		uint32_t GetSize() const { return mSize; }
		// バッファ使用法取得
		EBufferUsage GetUsage() const { return m_usage; }

		virtual void CreateObject() = 0;
		virtual void TransferData(void* transfer_data) = 0;

	};

	class RHITexture : public RHIResource
	{
	private:
		uint32_t m_width;
		uint32_t m_height;

	public:
		RHITexture()
			: RHIResource(ERHIResourceType::Texture)
			, m_width()
			, m_height()
		{

		}
		virtual ~RHITexture() {}

		// 幅取得
		uint32_t GetWidth() const { return m_width; }
		// 高さ取得
		uint32_t GetHeight() const { return m_height; }
	};

	class RHITexture2D : public RHITexture
	{
	public:
		RHITexture2D()
			: RHITexture()
		{

		}

		~RHITexture2D() {}

	};

}