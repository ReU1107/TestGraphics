#pragma once
#include "VulkanDevice.h"
#include "RHI/RHICommandBuffer.h"
#include <vector>

namespace Alpha
{
	class VulkanCommandBuffer : public RHICommandBuffer, public VulkanDeviceObject
	{
	private:
		std::vector<VkCommandBuffer> mCommandBuffers{};
		VkCommandPool mCommandPool{ VK_NULL_HANDLE };
	public:
		VulkanCommandBuffer(VulkanDevice* device);
		~VulkanCommandBuffer();

		void Create(uint32_t count);

		VkCommandBuffer GetCommandBuffer(const uint32_t index) const;

	};

}