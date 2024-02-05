#pragma once
#include <cstdint>

namespace Alpha
{
	class RHICommandBuffer;

	class CommandList
	{
	private:
		RHICommandBuffer* mRHI;

	public:

		void Begin(uint32_t current_index);

		void End();
	};

}