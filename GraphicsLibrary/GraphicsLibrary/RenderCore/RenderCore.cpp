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

#include "Vulkan/VulkanBuffer.h"
#include "Math/Vector.h"

namespace Alpha
{
	//Swapchain* swapchain = nullptr;
	//CommandList* list = nullptr;
	//CommandQueue* queue = nullptr;

	RHISwapchain* swapchain = nullptr;
	RHICommandBuffer* list = nullptr;
	RHICommandBuffer* copy_list = nullptr;
	RHICommandQueue* queue = nullptr;
	RHICommandQueue* copy = nullptr;

	RHIBuffer* vertex_buffer = nullptr;
	RHIBuffer* vertex_staging_buffer = nullptr;

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
			desc.Count = 3;
			list = RHIBuilder::CreateCommandBuffer(desc);
			desc.Count = 1;
			copy_list = RHIBuilder::CreateCommandBuffer(desc);
		}

		{
			RHICommandQueueDesc desc = {};
			queue = RHIBuilder::CreateCommandQueue(desc);

		}

		{
			RHIBufferDesc desc = {};
			desc.Usage = EBufferUsage::Vertex;
			desc.Stride = sizeof(float3);
			desc.Size = desc.Stride * 3;
			vertex_buffer = RHIBuilder::CreateBuffer(desc);
			desc.Usage = EBufferUsage::Staging;
			vertex_staging_buffer = RHIBuilder::CreateBuffer(desc);
		}
		std::vector<float3> vertices = {
			float3(0.0f,0.5f,0.0f),
			float3(0.5f,-0.5f,0.0f),
			float3(-0.5f,-0.5f,0.0f)
		};

		vertex_staging_buffer->TransferData(vertices.data());

		copy_list->Begin(0);
		copy_list->CopyBuffer(vertex_staging_buffer, vertex_buffer);

		copy_list->End();

		queue->Begin();
		queue->ExecuteCommandBuffer(copy_list);
		queue->Wait();


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