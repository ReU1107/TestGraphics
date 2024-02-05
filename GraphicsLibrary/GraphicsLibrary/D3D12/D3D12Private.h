#pragma once


#include "RHI/RHITypes.h"
#include "Utility/EnumClassFlags.h"

namespace Alpha
{
	inline D3D12_COMMAND_LIST_TYPE GetD3D12CommandListType(RHICommandType type)
	{
		switch (type)
		{
		default: return D3D12_COMMAND_LIST_TYPE_DIRECT;
		case RHICommandType::Direct: return D3D12_COMMAND_LIST_TYPE_DIRECT;
		case RHICommandType::Bundle: return D3D12_COMMAND_LIST_TYPE_BUNDLE;
		case RHICommandType::Compute: return D3D12_COMMAND_LIST_TYPE_COMPUTE;
		case RHICommandType::Copy: return D3D12_COMMAND_LIST_TYPE_COPY;
		}
	}

	inline D3D12_DESCRIPTOR_HEAP_TYPE GetD3D12DescriptorHeapType(RHIDescriptorHeapType type)
	{
		switch (type)
		{
		default: return D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		case RHIDescriptorHeapType::SRV: return D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		case RHIDescriptorHeapType::RTV: return D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		case RHIDescriptorHeapType::DSV: return D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
		case RHIDescriptorHeapType::Sampler: return D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER;
		}
	}

	inline D3D12_RESOURCE_DIMENSION GetD3D12ResourceDimension(RHIResourceDimension dimension)
	{
		switch (dimension)
		{
		default: return D3D12_RESOURCE_DIMENSION_BUFFER;
		case RHIResourceDimension::Unknown: return D3D12_RESOURCE_DIMENSION_BUFFER;
		case RHIResourceDimension::None: return D3D12_RESOURCE_DIMENSION_BUFFER;
		case RHIResourceDimension::Any: return D3D12_RESOURCE_DIMENSION_BUFFER;
		case RHIResourceDimension::Tex1D: return D3D12_RESOURCE_DIMENSION_TEXTURE1D;
		case RHIResourceDimension::Tex2D: return D3D12_RESOURCE_DIMENSION_TEXTURE2D;
		case RHIResourceDimension::Tex3D: return D3D12_RESOURCE_DIMENSION_TEXTURE3D;
		case RHIResourceDimension::Cube: return D3D12_RESOURCE_DIMENSION_TEXTURE1D;
		case RHIResourceDimension::Tex2DArray: return D3D12_RESOURCE_DIMENSION_TEXTURE1D;
		case RHIResourceDimension::CubeArray: return D3D12_RESOURCE_DIMENSION_TEXTURE1D;
		}
	}

	inline D3D_PRIMITIVE_TOPOLOGY GetD3D12PrimitiveTopology(RHIPrimitiveTopology topology)
	{
		switch (topology)
		{
		default: return D3D_PRIMITIVE_TOPOLOGY_UNDEFINED;
		case RHIPrimitiveTopology::Umdefined: return D3D_PRIMITIVE_TOPOLOGY_UNDEFINED;
		case RHIPrimitiveTopology::PointList: return D3D_PRIMITIVE_TOPOLOGY_POINTLIST;
		case RHIPrimitiveTopology::LineList: return D3D_PRIMITIVE_TOPOLOGY_LINELIST;
		case RHIPrimitiveTopology::LineStrip: return D3D_PRIMITIVE_TOPOLOGY_LINESTRIP;
		case RHIPrimitiveTopology::TriangleList: return D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		case RHIPrimitiveTopology::TriangleStrip: return D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
		}
	}

	inline D3D12_RESOURCE_STATES GetD3D12ResourceStates(RHIResourceState states)
	{
		D3D12_RESOURCE_STATES resourceStates = D3D12_RESOURCE_STATE_COMMON;

		if (EnumHasFlag(states, RHIResourceState::VertexConstantBuffer))
		{
			resourceStates |= D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER;
		}
		if (EnumHasFlag(states, RHIResourceState::IndexBuffer))
		{
			resourceStates |= D3D12_RESOURCE_STATE_INDEX_BUFFER;
		}
		if (EnumHasFlag(states, RHIResourceState::RenderTarget))
		{
			resourceStates |= D3D12_RESOURCE_STATE_RENDER_TARGET;
		}
		if (EnumHasFlag(states, RHIResourceState::UnorderedAccess))
		{
			resourceStates |= D3D12_RESOURCE_STATE_UNORDERED_ACCESS;
		}
		if (EnumHasFlag(states, RHIResourceState::DepthWrite))
		{
			resourceStates |= D3D12_RESOURCE_STATE_DEPTH_WRITE;
		}
		if (EnumHasFlag(states, RHIResourceState::DepthRead))
		{
			resourceStates |= D3D12_RESOURCE_STATE_DEPTH_READ;
		}
		if (EnumHasFlag(states, RHIResourceState::NonPixelShaderResource))
		{
			resourceStates |= D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE;
		}
		if (EnumHasFlag(states, RHIResourceState::PixelShaderResource))
		{
			resourceStates |= D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
		}
		if (EnumHasFlag(states, RHIResourceState::StreamOut))
		{
			resourceStates |= D3D12_RESOURCE_STATE_STREAM_OUT;
		}
		if (EnumHasFlag(states, RHIResourceState::IndirectArgument))
		{
			resourceStates |= D3D12_RESOURCE_STATE_INDIRECT_ARGUMENT;
		}
		if (EnumHasFlag(states, RHIResourceState::CopyDestination))
		{
			resourceStates |= D3D12_RESOURCE_STATE_COPY_DEST;
		}
		if (EnumHasFlag(states, RHIResourceState::CopySource))
		{
			resourceStates |= D3D12_RESOURCE_STATE_COPY_SOURCE;
		}
		if (EnumHasFlag(states, RHIResourceState::ResolveDestination))
		{
			resourceStates |= D3D12_RESOURCE_STATE_RESOLVE_DEST;
		}
		if (EnumHasFlag(states, RHIResourceState::ResolveSource))
		{
			resourceStates |= D3D12_RESOURCE_STATE_RESOLVE_SOURCE;
		}
		if (EnumHasFlag(states, RHIResourceState::RaytracingStructure))
		{
			resourceStates |= D3D12_RESOURCE_STATE_RAYTRACING_ACCELERATION_STRUCTURE;
		}
		if (EnumHasFlag(states, RHIResourceState::Present))
		{
			resourceStates |= D3D12_RESOURCE_STATE_PRESENT;
		}
		//if ((states & ResourceStates::GenericRead) != 0)
		//{
		//	resourceStates |= D3D12_RESOURCE_STATE_GENERIC_READ;
		//}

		return resourceStates;
	}

	inline D3D12_RESOURCE_FLAGS GetD3D12ResourceFlags(RHIResourceFlags flags)
	{
		D3D12_RESOURCE_FLAGS resourceFlags = D3D12_RESOURCE_FLAG_NONE;
		{
			if (EnumHasFlag(flags, RHIResourceFlags::AllowRenderTarget))
			{
				resourceFlags |= D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;
			}
			if (EnumHasFlag(flags, RHIResourceFlags::AllowDepthStencil))
			{
				resourceFlags |= D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
			}
			if (EnumHasFlag(flags, RHIResourceFlags::AllowUnorderedAccess))
			{
				resourceFlags |= D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
			}
			if (EnumHasFlag(flags, RHIResourceFlags::DenyShaderResource))
			{
				resourceFlags |= D3D12_RESOURCE_FLAG_DENY_SHADER_RESOURCE;
			}
			if (EnumHasFlag(flags, RHIResourceFlags::AllowCrossAdapter))
			{
				resourceFlags |= D3D12_RESOURCE_FLAG_ALLOW_CROSS_ADAPTER;
			}
			if (EnumHasFlag(flags, RHIResourceFlags::AllowSimultaneousAccess))
			{
				resourceFlags |= D3D12_RESOURCE_FLAG_ALLOW_SIMULTANEOUS_ACCESS;
			}
			if (EnumHasFlag(flags, RHIResourceFlags::DecodeReferenceOnly))
			{
				resourceFlags |= D3D12_RESOURCE_FLAG_VIDEO_DECODE_REFERENCE_ONLY;
			}
		}
		return resourceFlags;
	}

	inline DXGI_FORMAT GetDXGIFormat(RHIResourceFormat format)
	{
		switch (format)
		{
		default: return DXGI_FORMAT_R8G8B8A8_UINT;
		case RHIResourceFormat::RGBA32UInt: return DXGI_FORMAT_R8G8B8A8_UINT;
		case RHIResourceFormat::RGBA32SInt: return DXGI_FORMAT_R8G8B8A8_SINT;
		case RHIResourceFormat::RGBAFloat: return DXGI_FORMAT_R32G32B32A32_FLOAT;
		case RHIResourceFormat::RGBAHalf: return DXGI_FORMAT_R16G16B16A16_FLOAT;
		case RHIResourceFormat::RGBAUnorm: return DXGI_FORMAT_R8G8B8A8_UNORM;
		case RHIResourceFormat::RGBFloat: return DXGI_FORMAT_R32G32B32_FLOAT;
		case RHIResourceFormat::RGFloat: return DXGI_FORMAT_R32G32_FLOAT;
		case RHIResourceFormat::RFloat: return DXGI_FORMAT_R32_FLOAT;
		case RHIResourceFormat::RUInt: return DXGI_FORMAT_R32_UINT;
		case RHIResourceFormat::RGHalf: return DXGI_FORMAT_R16G16_FLOAT;
		case RHIResourceFormat::RHalf: return DXGI_FORMAT_R16_FLOAT;
		case RHIResourceFormat::Depth32: return DXGI_FORMAT_D32_FLOAT;
		case RHIResourceFormat::Depth16: return DXGI_FORMAT_D16_UNORM;
		case RHIResourceFormat::Depth24Stencil8: return DXGI_FORMAT_D24_UNORM_S8_UINT;
		case RHIResourceFormat::RGB10A2Unorm: return DXGI_FORMAT_R10G10B10A2_UNORM;
		}
	}
}