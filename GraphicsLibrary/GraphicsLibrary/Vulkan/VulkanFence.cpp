#include "VulkanFence.h"

namespace Alpha
{
	VulkanFence::VulkanFence(VulkanDevice* device)
		: RHIFence()
		, VulkanDeviceChild(device)
	{

	
	}

	VulkanFence::~VulkanFence()
	{
	}

	void VulkanFence::Create()
	{
		auto device = GetVkLogicalDevice();
		VkFenceCreateInfo fence_info = {};
		fence_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		VkFence fence = VK_NULL_HANDLE;
		auto result = vkCreateFence(device, &fence_info, nullptr, &fence);
		if (result != VK_SUCCESS)
		{

		}
	}
}