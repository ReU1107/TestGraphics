#pragma once
#include "RHI/RHIDescriptorHeap.h"
#include "VulkanDevice.h"

namespace Alpha
{
	class VulkanDescriptorHeap : public RHIDescriptorHeap, public VulkanDeviceChild
	{
	private:
		VkDescriptorPool mPool{ VK_NULL_HANDLE };

	public:
		VulkanDescriptorHeap(VulkanDevice* device);
		~VulkanDescriptorHeap();

		VkDescriptorPool GetNativeHandle() const { return mPool; }

		virtual void Create(const RHIDescriptorHeapDesc& desc) override;


	};


}