#pragma once


namespace Alpha
{
	// ���s����^�C�~���O
	//enum class Execute
	//{
	//
	//};

	class D3D12GraphicsPipelineState;
	class D3D12EffectShader;

	class RenderCommand
	{
		// std::function<void()>;
		// priority;
		// operator<() priority��r
	};

	class RenderGraphPass
	{
	private:
		D3D12GraphicsPipelineState* m_pipeline;
		D3D12EffectShader* m_shader;
		//std::vector<RenderCommand*>
	public:
		RenderGraphPass();
		~RenderGraphPass();

		//void SetPipeline(D3D12CommandList* list);

	};

	/*
	�{���͂��̃p�X���p�������N���X���쐬��
	�p�X���L�̏���(�R�}���h�ς�)���s���K�v������

	*/
}