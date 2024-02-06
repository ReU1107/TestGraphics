#include "CommandList.h"
#include "RHI/RHICommandBuffer.h"
#include "Utility/SmartPointer.h"
#include "RHIBuilder.h"

namespace Alpha
{
	CommandList::CommandList()
	{
		RHICommandBufferDesc desc;
		mRHI = RHIBuilder::CreateCommandBuffer(desc);
	}

	CommandList::~CommandList()
	{
		AlphaDelete(mRHI);
	}

	void CommandList::Begin(uint32_t current_index)
	{
		mRHI->Begin(current_index);
	}

	void CommandList::End()
	{
		mRHI->End();
	}
}