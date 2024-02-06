#pragma once
#include "VulkanDevice.h"
#include "RHI/RHICommandQueue.h"

#include <vector>

namespace Alpha
{
	class RHISwapchain;
	class RHICommandBuffer;

	class VulkanCommandQueue : public RHICommandQueue, public VulkanDeviceObject
	{
	private:
		VkQueue mQueue{ VK_NULL_HANDLE };
		VkFence mFence{ VK_NULL_HANDLE };
		//std::vector<VkSemaphore> mCurrentSemaphores{};
		VkSemaphore mCurrentSemaphore{ VK_NULL_HANDLE };
	public:
		VulkanCommandQueue(VulkanDevice* device);
		~VulkanCommandQueue();


		void Create(uint32_t index);

		// 
		virtual void Begin() override;
		// 
		virtual void SetWaitSemaphore(RHISwapchain* swapchain_) override;
		// ‚¢‚Â‚©‚±‚Á‚¿‚É•Ï‚¦‚é
		//virtual void SetWaitSemaphore(RHISemaphore* semaphore_);

		virtual void ExecuteCommandBuffer(RHICommandBuffer* command_buffer_) override;

		virtual void Wait() override;

		virtual void Present(RHISwapchain* swapchain) override;

	};

}