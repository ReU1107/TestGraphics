//#pragma once
//
///*
//DirectX�Ȃǂ�api�����b�s���O��������
//api�̏������Ȃ�ׂ������Ȃ��悤�ɂ���
//
//���݂�D3D12�Z�Z�N���X���g�p���Ă��邪���ꂪ�{����RHI�ɂȂ��Ă��Ȃ��Ƃ����Ȃ�
//*/
//
//#include <cstdint>
//#include <vector>
//#include "RHI/RHIResource.h"
//
//namespace Alpha
//{
//
//
//	class RenderResource
//	{
//	public:
//		RenderResource();
//		~RenderResource();
//
//		//void Transition(D3D12CommandList* list, D3D12ResourceState state);
//
//		virtual RHIResource* GetRHI() const = 0;
//
//	};
//
//
//	class RenderBuffer : public RenderResource
//	{
//	private:
//		RHIBuffer* m_rhi;
//
//	public:
//		virtual RHIResource* GetRHI() const override { return m_rhi; }
//	};
//
//	class VertexBuffer : public RenderBuffer
//	{
//	public:
//		VertexBuffer() : RenderBuffer() {}
//		~VertexBuffer() {}
//	};
//
//	class IndexBuffer : public RenderBuffer
//	{
//	public:
//		IndexBuffer() : RenderBuffer() {}
//		~IndexBuffer() {}
//	};
//
//	class UniformBuffer : public RenderBuffer
//	{
//
//	public:
//		UniformBuffer();
//		~UniformBuffer();
//
//		void Create(uint32_t stride, uint32_t num, bool dynamic = true);
//		void Init(const void* data);
//		void Update(const void* data);
//	};
//
//	struct TextureInfo
//	{
//
//	};
//
//	class Texture : public RenderResource
//	{
//	protected:
//		TextureInfo m_info;
//	public:
//		Texture();
//		~Texture();
//
//		void Create(uint32_t width, uint32_t height, RHIResourceDimension dimension, D3D12ResourceFormat format);
//		void Init(std::vector<uint8_t>& data, UINT pixelSize);
//
//		void Create(uint32_t width, uint32_t height, uint32_t pixelSize, std::vector<uint8_t>& data);
//
//		void Load(const std::wstring& filePath);
//
//		void CreateShaderResourceView(D3D12DescriptorHeap* heap);
//
//		//void Init(const void* data);
//
//	};
//
//	struct RenderTextureInfo
//	{
//
//		TextureInfo tex;
//
//		UINT backBufferIndex;
//		bool isBackBuffer;
//	};
//
//	class D3D12DescriptorHeap;
//
//	class RenderTexture : public RenderResource
//	{
//	private:
//		UINT m_backBufferIndex;
//		bool m_isBackBuffer;
//
//	public:
//		RenderTexture();
//		~RenderTexture();
//
//		void Init(const RenderTextureInfo& info);
//
//		void CreateRenderTargetView(D3D12DescriptorHeap* heap);
//
//		void SetRenderTarget(D3D12CommandList* list);
//
//		void Clear(D3D12CommandList* list);
//	};
//}
//
//
