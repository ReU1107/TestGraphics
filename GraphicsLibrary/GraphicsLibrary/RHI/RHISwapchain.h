#pragma once
#include <cstdint>

namespace Alpha
{
	class RHICommandQueue;

	class RHISwapchain
	{
	private:
		uint32_t mWidth{ 0 };
		uint32_t mHeight{ 0 };
	public:
		virtual ~RHISwapchain() {}

		virtual void Begin() = 0;
		// Present含む
		virtual void End() = 0;

		virtual uint32_t GetCurrentBackBufferIndex() const = 0;


		void SetWidth(uint32_t width) { mWidth = width; }

		void SetHeight(uint32_t height) { mHeight = height; }

		uint32_t GetWidth() const { return mWidth; }
		
		uint32_t GetHeight() const { return mHeight; }

		//virtual void WaitQueue(RHICommandQueue* command_queue) = 0;

	};
}