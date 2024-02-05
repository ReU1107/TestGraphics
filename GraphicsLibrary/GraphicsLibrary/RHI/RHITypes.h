#pragma once
#include <cstdint>
#include "Utility/EnumClassFlags.h"

namespace Alpha
{
	enum class RHICommandType
	{
		Direct,
		Bundle,
		Compute,
		Copy,
	};

	enum class RHIDescriptorHeapType
	{
		SRV,
		UAV = SRV,
		CBV = SRV,
		RTV,
		DSV,
		Sampler,
	};

	enum class RHIResourceDimension
	{
		Unknown,	// �e�N�X�`���^�C�v������������Ă��Ȃ����A�s���ł��B
		None,		// �e�N�X�`�����w�肳��Ă��܂���B
		Any,		// ���ׂẴe�N�X�`���^�C�v�B
		Tex1D,		// 1D�e�N�X�`��
		Tex2D,		// 2D�e�N�X�`��(Texture2D)�B
		Tex3D,		// 3D�{�����[���e�N�X�`��(Texture3D)�B
		Cube,		// �L���[�u�}�b�v �e�N�X�`���B
		Tex2DArray,	// 2D�z��e�N�X�`��(Texture2DArray)�B
		CubeArray,	// Cubemap array texture(CubemapArray).
	};

	enum class ERHIResourceType
	{
		None,

		SamplerState,
		RasterizerState,
		DepthStencilState,
		BlendState,
		VertexDeclaration,
		VertexShader,
		MeshShader,
		AmplificationShader,
		PixelShader,
		GeometryShader,
		RayTracingShader,
		ComputeShader,
		GraphicsPipelineState,
		ComputePipelineState,
		RayTracingPipelineState,
		BoundShaderState,
		UniformBufferLayout,
		UniformBuffer,
		Buffer,
		Texture,
		Texture2D,
		Texture2DArray,
		Texture3D,
		TextureCube,
		TextureReference,
		TimestampCalibrationQuery,
		GPUFence,
		RenderQuery,
		RenderQueryPool,
		ComputeFence,
		Viewport,
		UnorderedAccessView,
		ShaderResourceView,
		RayTracingAccelerationStructure,
		StagingBuffer,
		CustomPresent,
		ShaderLibrary,
		PipelineBinaryLibrary,

		Num
	};


	enum class RHIResourceFlags
	{
		None = 0x0,						// �Ȃ�
		AllowRenderTarget = 0x01,		// �`���w�苖��
		AllowDepthStencil = 0x02,		// �[�x�A�X�e���V���������݋���
		AllowUnorderedAccess = 0x04,	// �R���s���[�g�V�F�[�_�[�̃A�N�Z�X����
		DenyShaderResource = 0x08,		// �V�F�[�_�[���\�[�X�w��s����
		AllowCrossAdapter = 0x10,		// �ʁX�̃A�_�v�^�[�ł̎g�p����
		AllowSimultaneousAccess = 0x20,	// 
		DecodeReferenceOnly = 0x40,		// 
	};

	EnumClassFlags(RHIResourceFlags);

	enum class RHIPrimitiveTopology
	{
		Umdefined = 0,
		PointList = 1,
		LineList = 2,
		LineStrip = 3,
		TriangleList = 4,
		TriangleStrip = 5,
	};

	enum class ERHIResourceState
	{
		Common = 0,							// �Ȃ�
		VertexConstantBuffer	 = 1 << 0,	// ���_,�萔�o�b�t�@
		IndexBuffer				 = 1 << 1,	// �C���f�b�N�X�o�b�t�@
		RenderTarget			 = 1 << 2,	// �����_�[�^�[�Q�b�g
		UnorderedAccess			 = 1 << 3,	// �A���I�[�_�[�h�A�N�Z�X
		DepthWrite				 = 1 << 4,	// �[�x��������
		DepthRead				 = 1 << 5,	// �[�x�ǂݍ���
		NonPixelShaderResource	 = 1 << 6,	// �s�N�Z���V�F�[�_�[���ł̃��\�[�X�Ƃ��Ĉ���Ȃ�
		PixelShaderResource		 = 1 << 7,	// �s�N�Z���V�F�[�_�[���Ń��\�[�X�Ƃ��Ĉ���
		StreamOut				 = 1 << 8,	// �X�g���[���A�E�g
		IndirectArgument		 = 1 << 9,	// ����
		CopyDestination			 = 1 << 10,	// �R�s�[��
		CopySource				 = 1 << 11,	// �R�s�[��
		ResolveDestination		 = 1 << 12,	// 
		ResolveSource			 = 1 << 13,	// 
		RaytracingStructure		 = 1 << 14,	// ���C�g���[�V���O�\����
		GenericRead = ((((					// ��ʓI�ȓǂݍ��ݗp�̃X�e�[�g
			(VertexConstantBuffer | IndexBuffer)
			| NonPixelShaderResource)
			| PixelShaderResource)
			| IndirectArgument) | CopySource),
		Present					 = 0x8000,	// �v���[���g
	};

	EnumClassFlags(ERHIResourceState);

	enum class EBufferUsage
	{
		None = 0x00,
		Vertex				 = 1 << 0,	// 
		Index				 = 1 << 1,	// �C���f�b�N�X�o�b�t�@
		Structured			 = 1 << 2,	// 
		ByteAddress			 = 1 << 3,	// 
		Static				 = 1 << 4,	// 
		UnorderedAccess		 = 1 << 5,	// 
		Uniform				 = 1 << 6,	// 
		Staging				 = 1 << 7,	// 

	};

	EnumClassFlags(EBufferUsage);

	enum class RHIResourceFormat
	{
		RGBA32UInt,
		RGBA32SInt,
		RGBAFloat,
		RGBAHalf,
		RGBAUnorm,
		RGBFloat,
		RGFloat,
		RFloat,
		RUInt,
		RGHalf,
		RHalf,
		Depth32,
		Depth16,
		Depth24Stencil8,
		RGB10A2Unorm,
		//Alpha8,				// �A���t�@�݂̂̃e�N�X�`��
		//ARGB4444,			// 1 �s�N�Z�� 16 �r�b�g�̃e�N�X�`���`�� �A���t�@�`�����l�����K�p����Ă��܂�
		//RGB24,				// Color texture format, 8 - bits per channel.
		//RGBA32,				// 1 �`�����l�������� 8 �r�b�g�ō\�����ꂽ�A���t�@�`�����l�������J���[�̃e�N�X�`���`��
		//ARGB32,				// 1 �`�����l�������� 8 �r�b�g�ō\�����ꂽ�A���t�@�`�����l�������J���[�̃e�N�X�`���`��
		//RGB565,				// 16 �r�b�g�J���[�̃e�N�X�`���`��
		//R16,				// Single channel(R) texture format, 16 bit integer.
		//DXT1,				// ���k���ꂽ�e�N�X�`���`��
		//DXT5,				// ���k���ꂽ�A���t�@���K�p����Ă���e�N�X�`���`��
		//RGBA4444,			// 1 �`�����l�������� 4 �r�b�g�ō\�����ꂽ�A���t�@�`�����l�������F�̃e�N�X�`���`��
		//RHalf,				// �X�J���[�l(R) �̃e�N�X�`���`�� 16 �r�b�g�̕��������_
		//RGHalf,				// 2 �F(RG) �̃e�N�X�`���`�� �e�`�����l�� 16 �r�b�g�̕��������_
		//RGBAHalf,			// RGB �J���[�ƃA���t�@�`�����l���̃e�N�X�`���`�� �e�`�����l���� 16 �r�b�g�̕��������_
		//RFloat,				// �X�J���[�l(R) �̃e�N�X�`���`�� 32 �r�b�g�̕��������_
		//RGFloat,			// 2 �F(RG) �̃e�N�X�`���`�� �e�`�����l�� 32 �r�b�g�̕��������_
		//RGBAFloat,			// RGB color and alpha texture format, 32 - bit floats per channel.
		//RG16,				// Two color(RG) texture format, 8 - bits per channel.
		//R8,					// Single channel(R) texture format, 8 bit integer.
	};

	enum class RHIShaderType
	{
		Vertex = 0x01,
		Pixel = 0x02,


		Compute = 0x10,
		RayTracing = 0x20,


	};

	EnumClassFlags(RHIShaderType);

}