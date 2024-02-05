#pragma once
#include "VulkanDevice.h"
#include "RHI/RHISwapchain.h"

#include <vector>
#ifdef _WIN64
#include <Windows.h>
#endif // _WIN64

namespace Alpha
{
	struct VulkanBackBuffer
	{
		VkImage Image{ VK_NULL_HANDLE };
		VkImageView ImageView{ VK_NULL_HANDLE };
	};

	class VulkanSwapchain : public RHISwapchain, public VulkanDeviceObject
	{
	public:
		VulkanSwapchain(VulkanDevice* device);
		virtual ~VulkanSwapchain();

		//uint32_t GetSwapchainCount() const { return mCount; }
		virtual void Present() override;

		// 
		void CreateSwapchain();

#ifdef _WIN64
		void CreateSurface(HWND hWnd);
#endif // _WIN64

	private:
		VkSwapchainKHR mSwapchain{ VK_NULL_HANDLE };
		VkSurfaceKHR mSurface{ VK_NULL_HANDLE };
		std::vector<VulkanBackBuffer> mBackBuffers;
	};

}