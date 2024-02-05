#include "VulkanSwapchain.h"
#include <Windows.h>
#include <vulkan/vulkan_win32.h>
#include <vector>

namespace Alpha
{
	VulkanSwapchain::VulkanSwapchain(VulkanDevice* device)
		: RHISwapchain()
		, VulkanDeviceObject(device)
	{

	}

	VulkanSwapchain::~VulkanSwapchain()
	{
		auto instance = GetVkInstance();
		auto device = GetVkLogicalDevice();

		for (auto& back_buffer : mBackBuffers)
		{
			vkDestroyImageView(device, back_buffer.ImageView, nullptr);

			vkDestroyImage(device, back_buffer.Image, nullptr);
		}
		vkDestroySurfaceKHR(instance, mSurface, nullptr);

		vkDestroySwapchainKHR(device, mSwapchain, nullptr);
	}

	void VulkanSwapchain::Present()
	{
		//VkPresentInfoKHR present_info = {};
		//present_info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		//present_info.pSwapchains = &mSwapchain;

		//vkQueuePresentKHR(, &present_info);
	}

	void VulkanSwapchain::CreateSwapchain()
	{
		auto logical_device = GetVkLogicalDevice();
		auto physical_device = GetVkPhysicalDevice();

		auto surface = mSurface;
		// �T�[�t�F�C�X���擾
		VkSurfaceCapabilitiesKHR capabilities = {};
		auto result = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physical_device, surface, &capabilities);
		if (result != VK_SUCCESS)
		{

		}
		uint32_t present_mode_count = 0;
		result = vkGetPhysicalDeviceSurfacePresentModesKHR(physical_device, surface, &present_mode_count, nullptr);
		std::vector<VkPresentModeKHR> present_modes(present_mode_count);
		result = vkGetPhysicalDeviceSurfacePresentModesKHR(physical_device, surface, &present_mode_count, present_modes.data());

		VkPhysicalDeviceFeatures features = {};
		vkGetPhysicalDeviceFeatures(physical_device, &features);
		// �T�|�[�g���Ă���t�H�[�}�b�g�擾
		uint32_t format_count = 0;
		vkGetPhysicalDeviceSurfaceFormatsKHR(physical_device, surface, &format_count, nullptr);
		std::vector<VkSurfaceFormatKHR> formats(format_count);
		vkGetPhysicalDeviceSurfaceFormatsKHR(physical_device, surface, &format_count, formats.data());


		uint32_t swapchain_count = capabilities.minImageCount + 1;
		// ���Ɋ�Â����X���b�v�`�F�C���쐬
		VkSwapchainCreateInfoKHR swapchain_info = {};
		swapchain_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		swapchain_info.surface = surface;

		swapchain_info.imageExtent = capabilities.currentExtent;
		swapchain_info.imageArrayLayers = capabilities.maxImageArrayLayers;
		swapchain_info.imageFormat = formats[0].format;
		swapchain_info.imageColorSpace = formats[0].colorSpace;
		swapchain_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
		swapchain_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;

		swapchain_info.minImageCount = swapchain_count;

		swapchain_info.presentMode = present_modes[0];
		swapchain_info.preTransform = capabilities.currentTransform;

		swapchain_info.clipped = true;
		swapchain_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

		VkSwapchainKHR swapchain = VK_NULL_HANDLE;
		result = vkCreateSwapchainKHR(logical_device, &swapchain_info, nullptr, &swapchain);

		mSurface = surface;
		mSwapchain = swapchain;

		// �X���b�v�`�F�C������o�b�N�o�b�t�@�̃C���[�W�擾
		uint32_t image_count = 0;
		result = vkGetSwapchainImagesKHR(logical_device, mSwapchain, &image_count, nullptr);
		std::vector<VkImage> images(image_count);
		result = vkGetSwapchainImagesKHR(logical_device, mSwapchain, &image_count, images.data());
		if (result != VK_SUCCESS)
		{

		}
		// �C���[�W�r���[�̍쐬
		VkImageViewCreateInfo image_view_info = {};
		image_view_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		image_view_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
		image_view_info.format = VK_FORMAT_B8G8R8A8_UNORM;
		image_view_info.components =
		{
			VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A
		};
		image_view_info.subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };

		for (uint32_t i = 0; i < image_count; i++)
		{
			image_view_info.image = images[i];
			VkImageView view = VK_NULL_HANDLE;
			auto result = vkCreateImageView(logical_device, &image_view_info, nullptr, &view);
			if (result != VK_SUCCESS)
			{

			}
			VulkanBackBuffer back_buffer = {};
			back_buffer.Image = images[i];
			back_buffer.ImageView = view;
			mBackBuffers.push_back(back_buffer);
		}

	}

#ifdef _WIN64
	void VulkanSwapchain::CreateSurface(HWND hWnd)
	{
		auto instance = GetVkInstance();

		// �T�[�t�F�C�X�̍쐬
		VkWin32SurfaceCreateInfoKHR surfaceInfo{};
		surfaceInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
		surfaceInfo.hinstance = GetModuleHandle(nullptr);
		surfaceInfo.hwnd = hWnd;

		VkSurfaceKHR surface = VK_NULL_HANDLE;
		auto result = vkCreateWin32SurfaceKHR(instance, &surfaceInfo, nullptr, &surface);
		if (result != VK_SUCCESS)
		{
			// device_info extensions�Ɂ@VK_KHR_swapchain��ǉ��������H
		}

		mSurface = surface;

	}
#endif // _WIN64


}