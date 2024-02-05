#pragma once
#include <vector>
#include <cstdint>

namespace Alpha
{
	class D3D12DescriptorHeap;
	class RenderTexture;

	class RenderTargetPool
	{
	private:
		D3D12DescriptorHeap* m_rtHeap;
		D3D12DescriptorHeap* m_dsHeap;

		std::vector<RenderTexture*> m_targets;

	public:
		RenderTargetPool();
		~RenderTargetPool();

		RenderTexture* GetRenderTarget(uint32_t index) const;

	};
}