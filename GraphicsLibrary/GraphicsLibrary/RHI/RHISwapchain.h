#pragma once
#include <cstdint>

namespace Alpha
{
	class RHICommandQueue;

	class RHISwapchain
	{
	public:
		virtual ~RHISwapchain() {}

		virtual void Begin() = 0;
		// Present含む
		virtual void End() = 0;

		virtual uint32_t GetCurrentBackBufferIndex() const = 0;

		//virtual void WaitQueue(RHICommandQueue* command_queue) = 0;

	};
}