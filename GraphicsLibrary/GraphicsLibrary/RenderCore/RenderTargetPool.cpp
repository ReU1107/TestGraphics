
#include "RenderTargetPool.h"

#include "RenderResource.h"

//#include "D3D12/D3D12Subsystem.h"
//#include "D3D12/D3D12DescriptorHeap.h"

namespace Alpha
{
	RenderTargetPool::RenderTargetPool()
	{
		//m_rtHeap = D3D12Subsystem::Get().CreateDescriptorHeap(D3D12DescriptorHeapType::RTV, FrameCount);
		//m_dsHeap = D3D12Subsystem::Get().CreateDescriptorHeap(D3D12DescriptorHeapType::DSV, 1);

		//for (UINT i = 0; i < FrameCount; i++)
		//{
		//	RenderTexture* texture = new RenderTexture();
		//	RenderTextureInfo info = {};
		//	info.backBufferIndex = i;
		//	info.isBackBuffer = true;
		//	texture->Init(info);
		//	texture->CreateRenderTargetView(m_rtHeap);

		//	m_targets.push_back(texture);
		//}

	}

	RenderTargetPool::~RenderTargetPool()
	{
		for (auto& target : m_targets)
		{
			delete target;
		}
		delete m_dsHeap;
		delete m_rtHeap;
	}

	RenderTexture* RenderTargetPool::GetRenderTarget(uint32_t index) const
	{
		return m_targets[index];
	}
}