#pragma once

namespace Alpha
{
	class RHICommandBuffer;
	class RHISwapchain;

	class RHICommandQueue
	{
	public:
		virtual ~RHICommandQueue() {}

		virtual void Begin() = 0;

		virtual void SetWaitSemaphore(RHISwapchain* swapchain_) = 0;

		virtual void ExecuteCommandBuffer(RHICommandBuffer* command_buffer_) = 0;

		virtual void Wait() = 0;

		virtual void Present(RHISwapchain* swapchain) = 0;

	};

}