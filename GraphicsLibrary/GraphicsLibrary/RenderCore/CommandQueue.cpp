#include "CommandQueue.h"
#include "RHIBuilder.h"
#include "Utility/SmartPointer.h"

namespace Alpha
{
	CommandQueue::CommandQueue()
	{
		RHICommandQueueDesc desc = {};
		mRHI = RHIBuilder::CreateCommandQueue(desc);
	}

	CommandQueue::~CommandQueue()
	{
		AlphaDelete(mRHI);
	}
}