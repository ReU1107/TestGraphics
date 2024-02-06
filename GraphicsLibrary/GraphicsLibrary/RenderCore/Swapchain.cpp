#include "Swapchain.h"
#include "RHIBuilder.h"
#include "Utility/SmartPointer.h"

#include "WindowSystem.h"

namespace Alpha
{

	Swapchain::Swapchain()
	{
		RHISwapchainDesc desc = {};
		desc.hWnd = WindowSystem::sHWnd;
		mRHI = RHIBuilder::CreateSwapchain(desc);
	}

	Swapchain::~Swapchain()
	{
		AlphaDelete(mRHI);
	}
}