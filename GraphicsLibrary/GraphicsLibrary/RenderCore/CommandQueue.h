#pragma once

namespace Alpha
{
	class RHICommandQueue;

	class CommandQueue
	{
	private:
		RHICommandQueue* mRHI{ nullptr };

	public:
		// コマンドリスト
		CommandQueue();
		// デストラクタ
		~CommandQueue();

		RHICommandQueue* GetRHI() const { return mRHI; }

		void WaitExecutionList();

		// 止まってほしいタイミングで呼ぶ
		void Signal();
		//void Signal(CommandFencePtr fence);
		// 
		void Wait();
		//void Wait(CommandQueuePtr queue);

		//void SetNName(const std::wstring& name);

	};
}