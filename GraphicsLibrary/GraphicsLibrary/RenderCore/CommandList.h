#pragma once
#include <cstdint>

namespace Alpha
{
	class RHICommandBuffer;

	class CommandList
	{
	private:
		RHICommandBuffer* mRHI{ nullptr };
		// ���̃R�}���h���X�g���ˑ����鏈���Q(�����Static)
	public:
		CommandList();
		~CommandList();

		void Begin(uint32_t current_index);

		void End();

		RHICommandBuffer* GetRHI() const { return mRHI; }
	};

}