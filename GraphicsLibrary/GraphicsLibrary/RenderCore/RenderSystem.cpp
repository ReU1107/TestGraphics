
#include "RenderSystem.h"

//#include "D3D12/WindowsSubsystem.h"
//#include "D3D12/D3D12Subsystem.h"


#include "RenderTargetPool.h"
#include "RenderResource.h"

//#include "D3D12/D3D12CommandList.h"
//#include "D3D12/D3D12Shader.h"

//#include "RenderGraphPass.h"

#include "Math/Vector3.h"

#include "Camera.h"
//#include "D3D12/D3D12DescriptorHeap.h"


class RenderSystem::Impl
{
public:

	RenderTargetPool* s_pool;
	RenderGraphPass* s_pass;

	PositionVertexBuffer* vertexBuffer;
	TexcoordVertexBuffer* texBuffer;
	IndexBuffer* indexBuffer;
	UniformBuffer* uniformBuffer;
	UniformBuffer* lightBuffer;
	Texture* whiteTexture;
	Texture* blueTexture;
	std::vector<Texture*> m_textures;

	D3D12DescriptorHeap* s_heap;
	Vector3 lightPos;

public:
	Impl(HWND hWnd, UINT width, UINT height);
	~Impl()
	{
		delete s_pool;

		D3D12Subsystem::Shutdown();

		WindowsSubsystem::Shutdown();
	}

	void Render();

	void Init();

	void Load();

	void CreateTexture(UINT width, UINT height, UINT bit, UINT8 pixels[]);

};


RenderSystem::Impl::Impl(HWND hWnd, UINT width, UINT height)
	: s_pool(nullptr)
	, s_pass(nullptr)
	, vertexBuffer(nullptr)
	, texBuffer(nullptr)
	, indexBuffer(nullptr)
	, uniformBuffer(nullptr)
	, whiteTexture(nullptr)
	, blueTexture(nullptr)
	, s_heap(nullptr)
{
	WindowsSubsystem::Startup();
	WindowsSubsystem::Get().SetHandle(hWnd);
	WindowsSubsystem::Get().SetWidth(width);
	WindowsSubsystem::Get().SetHeight(height);
	//MessageBox(nullptr,L"ウィンドウ初期化終了", L"", MB_OK);

	D3D12Subsystem::Startup();

	//MessageBox(nullptr, L"DirectX初期化終了", L"", MB_OK);

}

void RenderSystem::Impl::Init()
{
	s_pool = new RenderTargetPool();


	s_pass = new RenderGraphPass();

	s_heap = D3D12Subsystem::Get().CreateDescriptorHeap(D3D12DescriptorHeapType::SRV, 5);

}

struct Light
{
	Vector3 pos;
};


void RenderSystem::Impl::Load()
{
	//texture = new Texture();
	//texture->Load(L"C:/Users/owner/Downloads/フルル.jpg");
	//texture->CreateShaderResourceView(s_heap);

	std::vector<Vector3> vertices =
	{
		{ -1.0f, 0.0f, 1.0f }, // 頂点0
		{ 1.0f,  0.0f,  1.0f },
		{  -1.0f,  0.0f, -1.0f }, // 頂点3
		{  1.0f, 0.0f, -1.0f },
	};

	std::vector<Vector2> v = {
		{0.0f,0.0f},
		{1.0f,0.0f},
		{0.0f,1.0f},
		{1.0f,1.0f}
	};

	std::vector<UINT> indices =
	{
		0, 1, 2, 2,1,3,
	};


	vertexBuffer = new PositionVertexBuffer();
	vertexBuffer->Create((UINT)vertices.size());
	vertexBuffer->Init(vertices.data());

	texBuffer = new TexcoordVertexBuffer();
	texBuffer->Create((UINT)v.size());
	texBuffer->Init(v.data());

	indexBuffer = new IndexBuffer();
	indexBuffer->Create((UINT)indices.size());
	indexBuffer->Init(indices.data());

	struct CameraB
	{
		Matrix4x4 viewPro;
	};

	CameraB b = {};
	Camera camera;
	b.viewPro = camera.Get(Vector3(.0f, 2.0f, -1.0f), Vector3(0.0f, 0.0f, 0.0f));


	uniformBuffer = new UniformBuffer();
	uniformBuffer->Create(sizeof(CameraB), 1);
	uniformBuffer->Init(&b);

	Light light;
	light.pos = Vector3(0.0f, 5.0f, 0.0f);
	lightPos = light.pos;
	lightBuffer = new UniformBuffer();
	lightBuffer->Create(sizeof(Light), 1);
	lightBuffer->Init(&light);
	


	static const UINT TextureWidth = 256;
	static const UINT TextureHeight = 256;
	static const UINT TexturePixelSize = 4;    // The number of bytes used to represent a pixel in the texture.

	const UINT rowPitch = TextureWidth * TexturePixelSize;
	const UINT cellPitch = rowPitch >> 3;        // The width of a cell in the checkboard texture.
	const UINT cellHeight = TextureWidth >> 3;    // The height of a cell in the checkerboard texture.
	const UINT textureSize = rowPitch * TextureHeight;

	std::vector<UINT8> data(textureSize);
	UINT8* pData = &data[0];

	for (UINT n = 0; n < textureSize; n += TexturePixelSize)
	{
		pData[n] = 0xff;        // R
		pData[n + 1] = 0xff;    // G
		pData[n + 2] = 0xff;    // B
		pData[n + 3] = 0xff;    // A
	
	}

	whiteTexture = new Texture();
	whiteTexture->Create(TextureWidth, TextureHeight, TexturePixelSize, data);
	whiteTexture->CreateShaderResourceView(s_heap);


	for (UINT n = 0; n < textureSize; n += TexturePixelSize)
	{
		pData[n] = 0;        // R
		pData[n + 1] = 0;    // G
		pData[n + 2] = 0xff;    // B
		pData[n + 3] = 0xff;    // A
	}

	blueTexture = new Texture();
	blueTexture->Create(TextureWidth, TextureHeight, TexturePixelSize, data);
	blueTexture->CreateShaderResourceView(s_heap);

	D3D12Subsystem::Get().UploadBegin();
	D3D12Subsystem::Get().Upload((D3D12Texture*)whiteTexture->GetResource());
	D3D12Subsystem::Get().Upload((D3D12Texture*)blueTexture->GetResource());
	D3D12Subsystem::Get().UploadEnd();
}

void RenderSystem::Impl::CreateTexture(UINT width, UINT height, UINT bit, UINT8 pixels[])
{
	const UINT rowPitch = width * bit;
	const UINT textureSize = rowPitch * height;

	std::vector<UINT8> data(textureSize);


	UINT8* pData = &data[0];

	for (UINT n = 0; n < textureSize; n += bit)
	{
		int red = pixels[n + 2];
		int green = pixels[n + 1];
		int blue = pixels[n];

		pData[n]	 = red;		// R
		pData[n + 1] = green;   // G
		pData[n + 2] = blue;    // B
		pData[n + 3] = 0xff;    // A

	}

	auto texture = new Texture();
	texture->Create(width, height, bit, data);
	texture->CreateShaderResourceView(s_heap);
	m_textures.push_back(texture);
	D3D12Subsystem::Get().UploadBegin();
	D3D12Subsystem::Get().Upload((D3D12Texture*)texture->GetResource());
	D3D12Subsystem::Get().UploadEnd();
}

void RenderSystem::Impl::Render()
{
	auto list = D3D12Subsystem::Get().GetImmediateCommandList();

	D3D12Subsystem::Get().RenderBegin();

	RenderTexture* backBuffer = s_pool->GetRenderTarget(D3D12Subsystem::Get().GetCurrentIndex());
	backBuffer->Transition(list, D3D12ResourceState::RenderTarget);

	backBuffer->SetRenderTarget(list);

	backBuffer->Clear(list);

	s_pass->SetPipeline(list);

	list->SetSetDescriptorHeap(s_heap);

	if (m_textures.size() > 0)
	{
		for (int i = 0; i < m_textures.size(); i++)
		{
			auto tex = m_textures[i];
			list->SetGraphicsDescriptorTable(tex->GetResource()->GetShaderResourceView(), i + 2);
		}
	}
	else
	{
		list->SetGraphicsDescriptorTable(whiteTexture->GetResource()->GetShaderResourceView(), 2);
		list->SetGraphicsDescriptorTable(blueTexture->GetResource()->GetShaderResourceView(), 3);

	}


	list->SetUniformBuffer((D3D12Buffer*)uniformBuffer->GetResource(), 0);
	list->SetUniformBuffer((D3D12Buffer*)lightBuffer->GetResource(), 1);

	D3D12Buffer* buf[2] = { (D3D12Buffer*)vertexBuffer->GetResource(),(D3D12Buffer*)texBuffer->GetResource() };

	list->DrawIndex((D3D12Buffer*)indexBuffer->GetResource(), buf, 2);

	backBuffer->Transition(list, D3D12ResourceState::Present);

	D3D12Subsystem::Get().RenderEnd();

}



RenderSystem::RenderSystem(HWND hWnd, UINT width, UINT height)
{
	m_impl = new Impl(hWnd, width, height);
}

RenderSystem::~RenderSystem()
{
	delete m_impl;

}

void RenderSystem::Init()
{
	m_impl->Init();
}

void RenderSystem::Load()
{
	m_impl->Load();
}

void RenderSystem::Render()
{
	m_impl->Render();
}

void RenderSystem::Test(const char* m)
{
	//auto texture1 = new Texture();
	//texture1->Create(TextureWidth, TextureHeight, TexturePixelSize, data);
	//texture1->CreateShaderResourceView(s_heap);

	//D3D12Subsystem::Get().UploadBegin();
	//D3D12Subsystem::Get().Upload((D3D12Texture*)texture1->GetResource());
	//D3D12Subsystem::Get().UploadEnd();
}

void RenderSystem::CreateTexture(UINT width, UINT height, UINT bit, UINT8 pixels[])
{
	m_impl->CreateTexture(width, height, bit, pixels);
}

void RenderSystem::Translate(float dx, float dy)
{
	m_impl->lightPos.x += dx;
	m_impl->lightPos.y += dy;
	Light light;
	light.pos = m_impl->lightPos;

	m_impl->lightBuffer->Update(&light);
}

