#pragma once
#include <cstdint>

namespace Alpha
{
	class RHISwapchain;
	class RHITexture;
	class RHIBuffer;

	// 複数のコマンドバッファオブジェクトを持つ
	class RHICommandBuffer
	{
	public:
		virtual ~RHICommandBuffer(){}

		virtual void Begin(uint32_t) = 0;

		virtual void End() = 0;

		virtual void CopyBuffer(RHIBuffer* src, RHIBuffer* dst) = 0;

		virtual void Clear(RHISwapchain* swapchain_) = 0;
		//virtual void Clear(RHITexture* texture_) = 0;

		virtual void Transition(RHISwapchain* swapchain_) = 0;
		//virtual void Transition(RHITexture* texture_) = 0;
		//virtual void Transition(RHIBuffer* buffer_) = 0;

	};

}