#pragma once
#include "RHI/RHIDescriptorLayout.h"
#include "VulkanDevice.h"
#include <vector>

namespace Alpha
{

	class VulkanDescriptorLayout : public RHIDescriptorLayout, public VulkanDeviceChild
	{
	private:
		VkDescriptorSetLayout mDescriptorLayout{ VK_NULL_HANDLE };

	public:
		VulkanDescriptorLayout(VulkanDevice* device);
		~VulkanDescriptorLayout();

		VkDescriptorSetLayout GetNativeHandle() const { return mDescriptorLayout; }

		virtual void Create(RHIDescriptorLayoutDesc& desc) override;
	};

}