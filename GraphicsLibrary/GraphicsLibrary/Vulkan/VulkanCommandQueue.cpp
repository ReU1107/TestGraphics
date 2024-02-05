#include "VulkanCommandQueue.h"
namespace Alpha
{
	VulkanCommandQueue::VulkanCommandQueue(VulkanDevice* device)
		: RHICommandQueue()
		, VulkanDeviceObject(device)
	{
	}

	VulkanCommandQueue::~VulkanCommandQueue()
	{

	}

	void VulkanCommandQueue::Create(uint32_t index)
	{
		auto device = GetVkLogicalDevice();
		VkQueue queue = VK_NULL_HANDLE;

		// BitFlags���g�p���č쐬�ς݂̃L���[�ԍ�����쐬���Ȃ��悤�ɂ���
		index = this->GetGraphicsQueueFamilyIndex();

		vkGetDeviceQueue(device, index, 0, &queue);
		mQueue = queue;
	}

	void VulkanCommandQueue::ExecuteCommandBuffer()
	{
		VkSubmitInfo submit_info = {};
		submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

		auto queue = mQueue;
		vkQueueSubmit(queue, 1, &submit_info, VK_NULL_HANDLE);
	}
}