#pragma once

namespace Alpha
{
	class RHICommandQueue;

	class CommandQueue
	{
	private:
		RHICommandQueue* mRHI{ nullptr };

	public:
		// �R�}���h���X�g
		CommandQueue();
		// �f�X�g���N�^
		~CommandQueue();

		RHICommandQueue* GetRHI() const { return mRHI; }

		void WaitExecutionList();

		// �~�܂��Ăق����^�C�~���O�ŌĂ�
		void Signal();
		//void Signal(CommandFencePtr fence);
		// 
		void Wait();
		//void Wait(CommandQueuePtr queue);

		//void SetNName(const std::wstring& name);

	};
}