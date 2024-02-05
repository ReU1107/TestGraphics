#include "RenderCore.h"
#include "RHI.h"

#include "RHI/RHIDefinitions.h"

namespace Alpha
{
	RenderCore::RenderCore(HWND hWnd)
	{
		m_dynamic = new RenderHardwareInterface();
		RHISwapchainDesc desc = {};
		desc.hWnd = hWnd;
		
		auto swapchain = RHIBuilder::CreateSwapchain(desc);
	}

	RenderCore::~RenderCore()
	{
		

		delete m_dynamic;
	}
}