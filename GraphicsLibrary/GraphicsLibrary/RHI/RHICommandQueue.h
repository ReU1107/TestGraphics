#pragma once

namespace Alpha
{
	class RHICommandQueue
	{
	public:
		virtual ~RHICommandQueue() {}

		virtual void ExecuteCommandBuffer() = 0;

	};

}