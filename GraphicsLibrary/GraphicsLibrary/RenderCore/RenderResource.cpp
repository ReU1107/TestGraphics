//
//#include "RenderResource.h"
//
//namespace Alpha
//{
//	RenderResource::RenderResource()
//	{
//	}
//
//	RenderResource::~RenderResource()
//	{
//	}
//
//	//void RenderResource::Transition(D3D12CommandList* list, D3D12ResourceState state)
//	//{
//	//	list->TransitionResource(m_resource, state);
//	//}
//
//	Texture::Texture()
//	{
//	}
//
//	Texture::~Texture()
//	{
//	}
//
//	void Texture::Load(const std::wstring& filePath)
//	{
//		D3D12Texture* texture = D3D12Subsystem::Get().CreateTexture();
//		texture->Load(filePath);
//		m_resource = texture;
//	}
//
//	void Texture::Create(uint32_t width, uint32_t height, D3D12ResourceDimension dimension, D3D12ResourceFormat format)
//	{
//		D3D12Texture* texture = D3D12Subsystem::Get().CreateTexture();
//		texture->Create(width, height, dimension, format, D3D12ResourceFlags::None, D3D12ResourceState::CopyDestination);
//		m_resource = texture;
//	}
//
//	void Texture::Init(std::vector<uint32_t>& data, uint32_t pixelSize)
//	{
//		D3D12Texture* tex = (D3D12Texture*)m_resource;
//
//		tex->m_data = data;
//		D3D12_SUBRESOURCE_DATA subresource = {};
//
//		uint32_t width = ((D3D12Texture*)m_resource)->m_width;
//		uint32_t height = ((D3D12Texture*)m_resource)->m_height;
//
//		subresource.pData = &(tex->m_data);
//		subresource.RowPitch = width * pixelSize;
//		subresource.SlicePitch = subresource.RowPitch * height;
//
//		tex->m_subresources.push_back(subresource);
//	}
//
//	void Texture::Create(uint32_t width, uint32_t height, uint32_t pixelSize, std::vector<uint32_t8>& data)
//	{
//		D3D12Texture* texture = D3D12Subsystem::Get().CreateTexture();
//		texture->Create(width, height, pixelSize, data);
//		m_resource = texture;
//	}
//
//	void Texture::CreateShaderResourceView(D3D12DescriptorHeap* heap)
//	{
//		m_resource->CreateShaderResourceView(heap, heap->GetCurrentIndex());
//	}
//
//	//void Texture::Init(const void* data)
//	//{
//	//}
//
//	RenderTexture::RenderTexture()
//		: RenderResource()
//		, m_backBufferIndex()
//		, m_isBackBuffer(false)
//	{
//	}
//
//	RenderTexture::~RenderTexture()
//	{
//	}
//
//	void RenderTexture::Init(const RenderTextureInfo& info)
//	{
//		if (info.isBackBuffer)
//		{
//			m_resource = D3D12Subsystem::Get().CreateBackBufferTexture(info.backBufferIndex);
//			m_backBufferIndex = info.backBufferIndex;
//			m_isBackBuffer = true;
//		}
//		else
//		{
//			D3D12Texture* texture = D3D12Subsystem::Get().CreateTexture();
//			//texture->Create();
//			m_backBufferIndex = info.backBufferIndex;
//			m_resource = texture;
//		}
//
//	}
//
//	void RenderTexture::CreateRenderTargetView(D3D12DescriptorHeap* heap)
//	{
//		m_resource->CreateRenderTargetView(heap, m_backBufferIndex);
//	}
//
//	void RenderTexture::SetRenderTarget(D3D12CommandList* list)
//	{
//		list->SetRenderTarget((D3D12Texture*)m_resource);
//
//	}
//
//	void RenderTexture::Clear(D3D12CommandList* list)
//	{
//		float color[4] = { 0.0f,0.0f,0.0f,1.0f };
//		list->ClearRenderTarget((D3D12Texture*)m_resource, color);
//	}
//
//	UniformBuffer::UniformBuffer()
//		: RenderBuffer()
//	{
//	}
//
//	UniformBuffer::~UniformBuffer()
//	{
//	}
//
//	void UniformBuffer::Create(uint32_t stride, uint32_t num, bool dynamic)
//	{
//		auto buffer = D3D12Subsystem::Get().CreateBuffer();
//		buffer->Create(stride, num, 256, dynamic);
//		m_resource = buffer;
//	}
//
//	void UniformBuffer::Init(const void* data)
//	{
//		((D3D12Buffer*)m_resource)->Upload(data);
//	}
//
//	void UniformBuffer::Update(const void* data)
//	{
//		((D3D12Buffer*)m_resource)->Upload(data);
//	}
//}