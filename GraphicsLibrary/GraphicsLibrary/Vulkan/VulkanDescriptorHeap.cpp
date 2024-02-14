#include "VulkanDescriptorHeap.h"

#include <vector>

namespace Alpha
{
	VulkanDescriptorHeap::VulkanDescriptorHeap(VulkanDevice* device)
		: RHIDescriptorHeap()
		, VulkanDeviceObject(device)
	{

	}

	VulkanDescriptorHeap::~VulkanDescriptorHeap()
	{
		auto device = GetVkLogicalDevice();

		vkDestroyDescriptorPool(device, mPool, nullptr);
	}

	VkDescriptorType GetVkType(ERHIResourceType type)
	{
		switch (type)
		{
		case Alpha::ERHIResourceType::None:
			break;
		case Alpha::ERHIResourceType::SamplerState:
			break;
		case Alpha::ERHIResourceType::RasterizerState:
			break;
		case Alpha::ERHIResourceType::DepthStencilState:
			break;
		case Alpha::ERHIResourceType::BlendState:
			break;
		case Alpha::ERHIResourceType::VertexDeclaration:
			break;
		case Alpha::ERHIResourceType::VertexShader:
			break;
		case Alpha::ERHIResourceType::MeshShader:
			break;
		case Alpha::ERHIResourceType::AmplificationShader:
			break;
		case Alpha::ERHIResourceType::PixelShader:
			break;
		case Alpha::ERHIResourceType::GeometryShader:
			break;
		case Alpha::ERHIResourceType::RayTracingShader:
			break;
		case Alpha::ERHIResourceType::ComputeShader:
			break;
		case Alpha::ERHIResourceType::GraphicsPipelineState:
			break;
		case Alpha::ERHIResourceType::ComputePipelineState:
			break;
		case Alpha::ERHIResourceType::RayTracingPipelineState:
			break;
		case Alpha::ERHIResourceType::BoundShaderState:
			break;
		case Alpha::ERHIResourceType::UniformBufferLayout:
			break;
		case Alpha::ERHIResourceType::UniformBuffer:
			break;
		case Alpha::ERHIResourceType::Buffer:
			break;
		case Alpha::ERHIResourceType::Texture:
			break;
		case Alpha::ERHIResourceType::Texture2D:
			break;
		case Alpha::ERHIResourceType::Texture2DArray:
			break;
		case Alpha::ERHIResourceType::Texture3D:
			break;
		case Alpha::ERHIResourceType::TextureCube:
			break;
		case Alpha::ERHIResourceType::TextureReference:
			break;
		case Alpha::ERHIResourceType::TimestampCalibrationQuery:
			break;
		case Alpha::ERHIResourceType::GPUFence:
			break;
		case Alpha::ERHIResourceType::RenderQuery:
			break;
		case Alpha::ERHIResourceType::RenderQueryPool:
			break;
		case Alpha::ERHIResourceType::ComputeFence:
			break;
		case Alpha::ERHIResourceType::Viewport:
			break;
		case Alpha::ERHIResourceType::UnorderedAccessView:
			break;
		case Alpha::ERHIResourceType::ShaderResourceView:
			break;
		case Alpha::ERHIResourceType::RayTracingAccelerationStructure:
			break;
		case Alpha::ERHIResourceType::StagingBuffer:
			break;
		case Alpha::ERHIResourceType::CustomPresent:
			break;
		case Alpha::ERHIResourceType::ShaderLibrary:
			break;
		case Alpha::ERHIResourceType::PipelineBinaryLibrary:
			break;
		case Alpha::ERHIResourceType::Num:
			break;
		default:
			break;
		}
	}

	void VulkanDescriptorHeap::Create(const RHIDescriptorHeapDesc& desc)
	{
		auto device = GetVkLogicalDevice();

		std::vector<VkDescriptorPoolSize> parameters(desc.ParameterCount);

		for (uint32_t i = 0; i < desc.ParameterCount; i++)
		{
			auto& parameter = parameters[i];
			parameter.descriptorCount = desc.Parameter[i].ReservationCount;
			parameter.type;
		}

		VkDescriptorPoolCreateInfo pool_info = {};
		pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		pool_info.pPoolSizes = parameters.data();
		pool_info.poolSizeCount = parameters.size();
		pool_info.flags;//VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT ,VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT
		VkDescriptorPool pool = VK_NULL_HANDLE;

		vkCreateDescriptorPool(device, &pool_info, nullptr, &pool);
	}
}