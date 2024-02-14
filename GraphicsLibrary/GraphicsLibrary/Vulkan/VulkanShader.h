#pragma once
#include "RHI/RHIShader.h"
#include "VulkanDevice.h"

namespace Alpha
{
	class VulkanShader : public RHIShader, public VulkanDeviceObject
	{
	private:
		VkShaderModule mModule{ VK_NULL_HANDLE };

	public:
		VulkanShader(VulkanDevice* device);
		~VulkanShader();


		void Create(const char* file_directory);

		VkShaderModule GetModule() const { return mModule; }
	};

}
