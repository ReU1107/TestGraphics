#include "VulkanDescriptorView.h"
#include "VulkanDescriptorHeap.h"
#include "VulkanDescriptorLayout.h"

#include "VulkanBuffer.h"
#include "RHI/RHIDefinitions.h"

namespace Alpha
{
	VulkanDescriptorView::VulkanDescriptorView(VulkanDevice* device)
		: VulkanDeviceChild(device)
	{
	}

	VulkanDescriptorView::~VulkanDescriptorView()
	{
		//vkDestroyPipelineLayout();

		//vkFreeDescriptorSets();
	}
	
	void VulkanDescriptorView::Create(RHIDescriptorViewDesc& desc)
	{
		auto heap = static_cast<VulkanDescriptorHeap*>(desc.Heap);
		std::vector<VkDescriptorSetLayout> layouts(desc.LayoutCount);

		for (uint32_t i = 0; i < desc.LayoutCount; i++)
		{
			auto layout = static_cast<VulkanDescriptorLayout*>(desc.Layouts[i]);
			layouts[i] = layout->GetNativeHandle();
		}

		VkDescriptorSetAllocateInfo set_info = {};
		set_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		set_info.descriptorPool = heap->GetNativeHandle();
		set_info.pSetLayouts = layouts.data();
		set_info.descriptorSetCount = desc.LayoutCount;
		
		auto device = GetVkLogicalDevice();
		std::vector<VkDescriptorSet> sets(set_info.descriptorSetCount);
		vkAllocateDescriptorSets(device, &set_info, sets.data());

		VkPipelineLayoutCreateInfo layout_info = {};
		layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		layout_info.pSetLayouts = layouts.data();
		layout_info.setLayoutCount = layouts.size();

		VkPipelineLayout layout = VK_NULL_HANDLE;
		vkCreatePipelineLayout(device, &layout_info, nullptr, &layout);

		mPipelineLayout = layout;
		mSets = std::move(sets);

	}

	void VulkanDescriptorView::BindResource(RHIBuffer* buffer_, uint32_t set_index, uint32_t register_index)
	{
		auto buffer = static_cast<VulkanBuffer*>(buffer_);
		VkDescriptorBufferInfo info = {};
		info.buffer = buffer->GetNativeHandle();
		info.range = buffer->GetSize();

		VkWriteDescriptorSet write = {};
		write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		write.dstSet = mSets[set_index];
		write.dstBinding = register_index;
		write.dstArrayElement = 0;
		write.descriptorCount = 1;
		write.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;

		write.pBufferInfo = &info;

		auto device = GetVkLogicalDevice();

		vkUpdateDescriptorSets(device, 1, &write, 0, nullptr);
	}
}