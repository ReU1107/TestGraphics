#pragma once
#include "D3D12Common.h"
#include <string>

class ID3D12RootSignature;
class ID3DBlob;

namespace Alpha
{
	class D3D12RootSignature : public D3D12DeviceObject
	{
	private:
		ComPtr<ID3D12RootSignature> m_rootSignature;

	public:
		D3D12RootSignature(D3D12Device* device);
		D3D12RootSignature(D3D12Device* device, ID3DBlob* blob);
		~D3D12RootSignature();

		ID3D12RootSignature* GetNativeRootSignature() const { return m_rootSignature.Get(); }

	};

	class D3D12GraphicsPipelineState;

	class D3D12Shader : public D3D12DeviceObject
	{
	protected:
		ComPtr<ID3DBlob> m_blob;

	public:
		D3D12Shader(D3D12Device* device);
		~D3D12Shader();

		ID3DBlob* GetNativeShader() const { return m_blob.Get(); }

		//virtual void Apply(D3D12GraphicsPipelineState* pipeline) {};

	};

	class D3D12VertexShader : public D3D12Shader
	{
	public:
		D3D12VertexShader(D3D12Device* device, std::wstring& filePath);
		~D3D12VertexShader();

	};

	class D3D12PixelShader : public D3D12Shader
	{
	public:
		D3D12PixelShader(D3D12Device* device, std::wstring& filePath);
		~D3D12PixelShader();

	};

	class D3D12EffectShader : public D3D12Shader
	{
	private:
		D3D12RootSignature* m_rootSignature;

		D3D12VertexShader* m_vertexShader;
		D3D12PixelShader* m_pixelShader;

		RHIShaderType m_type;
	public:
		D3D12EffectShader(D3D12Device* device, std::wstring& filePath, RHIShaderType type);
		~D3D12EffectShader();

		D3D12RootSignature* GetRootSignature() const { return m_rootSignature; }


		void Apply(D3D12_GRAPHICS_PIPELINE_STATE_DESC* info);
	};


	class D3D12RayTracingShader
	{
		//https://github.com/EpicGames/UnrealEngine/blob/release/Engine/Source/Runtime/Renderer/Private/RayTracing/RayTracingAmbientOcclusion.cpp

	};


}