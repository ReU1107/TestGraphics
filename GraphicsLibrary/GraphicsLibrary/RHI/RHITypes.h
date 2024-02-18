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
		Unknown,	// テクスチャタイプが初期化されていないか、不明です。
		None,		// テクスチャが指定されていません。
		Any,		// すべてのテクスチャタイプ。
		Tex1D,		// 1Dテクスチャ
		Tex2D,		// 2Dテクスチャ(Texture2D)。
		Tex3D,		// 3Dボリュームテクスチャ(Texture3D)。
		Cube,		// キューブマップ テクスチャ。
		Tex2DArray,	// 2D配列テクスチャ(Texture2DArray)。
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

	enum class ERHIResourceViewType
	{
		None,

		UniformBuffer,
		Texture,
		Sampler,
	};

	enum class RHIResourceFlags
	{
		None = 0x0,						// なし
		AllowRenderTarget = 0x01,		// 描画先指定許可
		AllowDepthStencil = 0x02,		// 深度、ステンシル書き込み許可
		AllowUnorderedAccess = 0x04,	// コンピュートシェーダーのアクセス許可
		DenyShaderResource = 0x08,		// シェーダーリソース指定不許可
		AllowCrossAdapter = 0x10,		// 別々のアダプターでの使用許可
		AllowSimultaneousAccess = 0x20,	// 
		DecodeReferenceOnly = 0x40,		// 
	};

	EnumClassFlags(RHIResourceFlags);

	enum class ERHIPrimitiveTopology
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
		Common = 0,							// なし
		VertexConstantBuffer	 = 1 << 0,	// 頂点,定数バッファ
		IndexBuffer				 = 1 << 1,	// インデックスバッファ
		RenderTarget			 = 1 << 2,	// レンダーターゲット
		UnorderedAccess			 = 1 << 3,	// アンオーダードアクセス
		DepthWrite				 = 1 << 4,	// 深度書き込み
		DepthRead				 = 1 << 5,	// 深度読み込み
		NonPixelShaderResource	 = 1 << 6,	// ピクセルシェーダー内でのリソースとして扱わない
		PixelShaderResource		 = 1 << 7,	// ピクセルシェーダー内でリソースとして扱う
		StreamOut				 = 1 << 8,	// ストリームアウト
		IndirectArgument		 = 1 << 9,	// 即時
		CopyDestination			 = 1 << 10,	// コピー先
		CopySource				 = 1 << 11,	// コピー元
		ResolveDestination		 = 1 << 12,	// 
		ResolveSource			 = 1 << 13,	// 
		RaytracingStructure		 = 1 << 14,	// レイトレーシング構造体
		GenericRead = ((((					// 一般的な読み込み用のステート
			(VertexConstantBuffer | IndexBuffer)
			| NonPixelShaderResource)
			| PixelShaderResource)
			| IndirectArgument) | CopySource),
		Present					 = 0x8000,	// プレゼント
	};

	EnumClassFlags(ERHIResourceState);

	enum class EBufferUsage
	{
		None = 0x00,
		Vertex				 = 1 << 0,	// 
		Index				 = 1 << 1,	// インデックスバッファ
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
		//Alpha8,				// アルファのみのテクスチャ
		//ARGB4444,			// 1 ピクセル 16 ビットのテクスチャ形式 アルファチャンネルが適用されています
		//RGB24,				// Color texture format, 8 - bits per channel.
		//RGBA32,				// 1 チャンネルあたり 8 ビットで構成されたアルファチャンネルを持つカラーのテクスチャ形式
		//ARGB32,				// 1 チャンネルあたり 8 ビットで構成されたアルファチャンネルを持つカラーのテクスチャ形式
		//RGB565,				// 16 ビットカラーのテクスチャ形式
		//R16,				// Single channel(R) texture format, 16 bit integer.
		//DXT1,				// 圧縮されたテクスチャ形式
		//DXT5,				// 圧縮されたアルファが適用されているテクスチャ形式
		//RGBA4444,			// 1 チャンネルあたり 4 ビットで構成されたアルファチャンネルを持つ色のテクスチャ形式
		//RHalf,				// スカラー値(R) のテクスチャ形式 16 ビットの浮動小数点
		//RGHalf,				// 2 色(RG) のテクスチャ形式 各チャンネル 16 ビットの浮動小数点
		//RGBAHalf,			// RGB カラーとアルファチャンネルのテクスチャ形式 各チャンネルは 16 ビットの浮動小数点
		//RFloat,				// スカラー値(R) のテクスチャ形式 32 ビットの浮動小数点
		//RGFloat,			// 2 色(RG) のテクスチャ形式 各チャンネル 32 ビットの浮動小数点
		//RGBAFloat,			// RGB color and alpha texture format, 32 - bit floats per channel.
		//RG16,				// Two color(RG) texture format, 8 - bits per channel.
		//R8,					// Single channel(R) texture format, 8 bit integer.
	};

	enum class ERHIShaderFlags
	{
		Vertex				= 1 << 0,	// 
		Pixel				= 1 << 1,	// 
		Geometry			= 1 << 2,	// 
		Hull				= 1 << 3,	// 
		Domain				= 1 << 4,	// 
		Mesh				= 1 << 5,	// 
		Compute				= 1 << 6,	// 
		RayTracing			= 1 << 7,	// 

	};

	EnumClassFlags(ERHIShaderFlags);

}