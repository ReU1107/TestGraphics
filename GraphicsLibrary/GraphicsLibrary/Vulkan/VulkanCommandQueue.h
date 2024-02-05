#pragma once
#include "VulkanDevice.h"
#include "RHI/RHICommandQueue.h"

namespace Alpha
{
	class VulkanCommandQueue : public RHICommandQueue, public VulkanDeviceObject
	{
	private:
		VkQueue mQueue{ VK_NULL_HANDLE };

	public:
		VulkanCommandQueue(VulkanDevice* device);
		~VulkanCommandQueue();


		void Create(uint32_t index);

		virtual void ExecuteCommandBuffer() override;
	};

}