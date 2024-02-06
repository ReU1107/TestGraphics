#include "RenderCore.h"
#include "RHI.h"

#include "RHI/RHIDefinitions.h"
#include "Swapchain.h"
#include "CommandList.h"
#include "CommandQueue.h"
#include "RHIBuilder.h"

#include "WindowSystem.h"

#include "Vulkan/VulkanSwapchain.h"
#include "Vulkan/VulkanCommandBuffer.h"
#include "Vulkan/VulkanCommandQueue.h"

namespace Alpha
{
	//Swapchain* swapchain = nullptr;
	//CommandList* list = nullptr;
	//CommandQueue* queue = nullptr;

	RHISwapchain* swapchain = nullptr;
	RHICommandBuffer* list = nullptr;
	RHICommandQueue* queue = nullptr;

	RenderCore::RenderCore(HWND hWnd)
	{
		m_dynamic = new RenderHardwareInterface();

		{
			RHISwapchainDesc desc = {};
			desc.hWnd = WindowSystem::sHWnd;
			swapchain = RHIBuilder::CreateSwapchain(desc);
		}

		{
			RHICommandBufferDesc desc;
			list = RHIBuilder::CreateCommandBuffer(desc);
		}
		
		{
			RHICommandQueueDesc desc = {};
			queue = RHIBuilder::CreateCommandQueue(desc);
		}

	}

	void RenderCore::Draw()
	{
		swapchain->Begin();

		queue->Begin();
		queue->SetWaitSemaphore(swapchain);
		uint32_t current_index = swapchain->GetCurrentBackBufferIndex();
		list->Begin(current_index);

		list->Transition(swapchain);

		list->Clear(swapchain);

		list->Transition(swapchain);

		list->End();
		queue->ExecuteCommandBuffer(list);
		queue->Wait();
		queue->Present(swapchain);
		swapchain->End();

	}

	RenderCore::~RenderCore()
	{
		

		delete m_dynamic;
	}
}