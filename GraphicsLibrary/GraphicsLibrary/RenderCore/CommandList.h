#pragma once
#include <cstdint>

namespace Alpha
{
	class RHICommandBuffer;

	class CommandList
	{
	private:
		RHICommandBuffer* mRHI{ nullptr };
		// このコマンドリストが依存する処理群(これはStatic)
	public:
		CommandList();
		~CommandList();

		void Begin(uint32_t current_index);

		void End();

		RHICommandBuffer* GetRHI() const { return mRHI; }
	};

}