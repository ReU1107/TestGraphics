#pragma once
#include "VulkanDevice.h"
#include "RHI/RHICommandBuffer.h"
#include <vector>

namespace Alpha
{
	struct VulkanCommand
	{
		VkCommandBuffer Buffer{ VK_NULL_HANDLE };		// �R�}���h��ςރo�b�t�@
		VkSemaphore SignalSemaphore{ VK_NULL_HANDLE };	// �ς񂾃R�}���h���������đҋ@������
		//std::vector<VkSemaphore> WaitSemaphores{};			// ���̃R�}���h����������O�ɑ҂��Ȃ��Ƃ����Ȃ��Z�}�t�H�Q
	};

	class VulkanCommandBuffer : public RHICommandBuffer, public VulkanDeviceObject
	{
	private:
		std::vector<VulkanCommand> mCommands{};

		VkCommandPool mCommandPool{ VK_NULL_HANDLE };
		VkCommandBuffer mCurrentBuffer{ VK_NULL_HANDLE };
		VkSemaphore mCurrentSemaphore{ VK_NULL_HANDLE };
		

	public:
		VulkanCommandBuffer(VulkanDevice* device);
		~VulkanCommandBuffer();

		void Create(uint32_t count);

		VkCommandBuffer GetCommandBuffer(const uint32_t index) const;

		VkCommandBuffer GetCurrentCommandBuffer() const;

		VkSemaphore GetCurrentSemaphore() const;

		virtual void Clear(RHISwapchain* swapchain_) override final;

		virtual void Transition(RHISwapchain* swapchain_) override final;

		// ���z�֐�
		virtual void Begin(uint32_t) override final;

		virtual void End() override final;

	};

}