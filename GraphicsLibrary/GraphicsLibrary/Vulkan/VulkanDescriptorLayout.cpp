#include "VulkanDescriptorLayout.h"


namespace Alpha
{
	VulkanDescriptorLayout::VulkanDescriptorLayout(VulkanDevice* device)
		: VulkanDeviceObject(device)
	{
	}

	VulkanDescriptorLayout::~VulkanDescriptorLayout()
	{
	}

	void VulkanDescriptorLayout::Create()
	{
		auto device = GetVkLogicalDevice();

		VkDescriptorSetLayoutBinding binding;

		VkDescriptorSetLayoutCreateInfo descriptor_set_create_info;
		descriptor_set_create_info.sType =
			VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;

		descriptor_set_create_info.pBindings = &binding;

		VkDescriptorSetLayout descriptor_set_layout;

		vkCreateDescriptorSetLayout(device,)

	}
}