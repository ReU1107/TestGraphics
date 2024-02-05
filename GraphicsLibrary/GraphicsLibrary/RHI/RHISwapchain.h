#pragma once

namespace Alpha
{
	class RHISwapchain
	{
	public:
		virtual ~RHISwapchain() {}

		virtual void Present() = 0;
	};
}