#include "VulkanCommandBuffer.h"

namespace Alpha
{
	VulkanCommandBuffer::VulkanCommandBuffer(VulkanDevice* device)
		: RHICommandBuffer()
		, VulkanDeviceObject(device)
	{

	}

	VulkanCommandBuffer::~VulkanCommandBuffer()
	{
		auto device = GetVkLogicalDevice();
		vkFreeCommandBuffers(device, mCommandPool, mCommandBuffers.size(), mCommandBuffers.data());
		vkDestroyCommandPool(device, mCommandPool, nullptr);
	}

	void VulkanCommandBuffer::Create(uint32_t count)
	{
		auto device = GetVkLogicalDevice();

		uint32_t index = GetGraphicsQueueFamilyIndex();

		VkCommandPoolCreateInfo command_pool_info = {};
		command_pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		command_pool_info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
		command_pool_info.queueFamilyIndex = index;
		VkCommandPool command_pool = VK_NULL_HANDLE;
		auto result = vkCreateCommandPool(device, &command_pool_info, nullptr, &command_pool);
		if (result != VK_SUCCESS)
		{

		}

		VkCommandBufferAllocateInfo command_buffer_info = {};
		command_buffer_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		command_buffer_info.commandPool = command_pool;
		command_buffer_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		command_buffer_info.commandBufferCount = count;

		std::vector<VkCommandBuffer> command_buffers(count);
		result = vkAllocateCommandBuffers(device, &command_buffer_info, command_buffers.data());
		if (result != VK_SUCCESS)
		{

		}
		mCommandPool = command_pool;
		mCommandBuffers = command_buffers;
	}

	VkCommandBuffer VulkanCommandBuffer::GetCommandBuffer(const uint32_t index) const
	{
		return VkCommandBuffer();
	}
}