#pragma once
#include "D3D12Common.h"

class ID3D12PipelineState;

namespace Alpha
{
	class D3D12Shader;
	class D3D12RootSignature;
	class D3D12EffectShader;

	class D3D12GraphicsPipelineState : public D3D12DeviceObject
	{
	private:
		ComPtr<ID3D12PipelineState> m_pipelineState;

	public:
		D3D12GraphicsPipelineState(D3D12Device* device);
		~D3D12GraphicsPipelineState();


		void CreateByFX(D3D12Shader* vertexShader, D3D12Shader* pixelShader, D3D12RootSignature* rootSignature);

		// 
		void Create(D3D12EffectShader* shader);

		ID3D12PipelineState* GetNativePipelineState() const { return m_pipelineState.Get(); }

	};


	class D3D12ComputePipelineState
	{

	};
}