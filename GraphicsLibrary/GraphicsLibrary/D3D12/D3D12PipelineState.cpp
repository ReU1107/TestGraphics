#include <d3d12.h>
#include "D3D12PipelineState.h"

#include "D3D12Device.h"
#include "D3D12Shader.h"
namespace Alpha
{
    static D3D12_BLEND_DESC GetDefaultBlendDesc()
    {
        D3D12_BLEND_DESC desc = {};
        desc.AlphaToCoverageEnable = false;
        desc.IndependentBlendEnable = false;
        const D3D12_RENDER_TARGET_BLEND_DESC defaultRenderTargetBlendDesc =
        {
            FALSE,FALSE,
            D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD,
            D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD,
            D3D12_LOGIC_OP_NOOP,
            D3D12_COLOR_WRITE_ENABLE_ALL,
        };
        for (UINT i = 0; i < D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i)
            desc.RenderTarget[i] = defaultRenderTargetBlendDesc;
        return desc;
    }

    static D3D12_RASTERIZER_DESC GetDefaultRasterizerDesc()
    {
        D3D12_RASTERIZER_DESC desc = {};
        desc.FillMode = D3D12_FILL_MODE_SOLID;
        desc.CullMode = D3D12_CULL_MODE_BACK;
        desc.FrontCounterClockwise = FALSE;
        desc.DepthBias = D3D12_DEFAULT_DEPTH_BIAS;
        desc.DepthBiasClamp = D3D12_DEFAULT_DEPTH_BIAS_CLAMP;
        desc.SlopeScaledDepthBias = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
        desc.DepthClipEnable = TRUE;
        desc.MultisampleEnable = FALSE;
        desc.AntialiasedLineEnable = FALSE;
        desc.ForcedSampleCount = 0;
        desc.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
        return desc;
    }

    D3D12GraphicsPipelineState::D3D12GraphicsPipelineState(D3D12Device* device)
        : D3D12DeviceObject(device)
    {

    }

    D3D12GraphicsPipelineState::~D3D12GraphicsPipelineState()
    {
    }

    void D3D12GraphicsPipelineState::CreateByFX(D3D12Shader* vertexShader, D3D12Shader* pixelShader, D3D12RootSignature* rootSignature)
    {
        D3D12_INPUT_ELEMENT_DESC inputElementDescs[] =
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
            { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
        };

        // Describe and create the graphics pipeline state object (PSO).
        D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
        psoDesc.InputLayout = { inputElementDescs, _countof(inputElementDescs) };
        psoDesc.pRootSignature = rootSignature->GetNativeRootSignature();
        psoDesc.VS.pShaderBytecode = vertexShader->GetNativeShader()->GetBufferPointer();
        psoDesc.VS.BytecodeLength = vertexShader->GetNativeShader()->GetBufferSize();
        psoDesc.PS.pShaderBytecode = pixelShader->GetNativeShader()->GetBufferPointer();
        psoDesc.PS.BytecodeLength = pixelShader->GetNativeShader()->GetBufferSize();
        psoDesc.RasterizerState = GetDefaultRasterizerDesc();
        psoDesc.BlendState = GetDefaultBlendDesc();
        psoDesc.DepthStencilState.DepthEnable = FALSE;
        psoDesc.DepthStencilState.StencilEnable = FALSE;
        psoDesc.SampleMask = UINT_MAX;
        psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
        psoDesc.NumRenderTargets = 1;
        psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
        psoDesc.SampleDesc.Count = 1;
        FAILED(m_device->GetNativeDevice()->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&m_pipelineState)));
    }

    void D3D12GraphicsPipelineState::Create(D3D12EffectShader* shader)
    {
        // TODO:頂点レイアウトも違う形で適用させる必要がある

        D3D12_INPUT_ELEMENT_DESC inputElementDescs[] =
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
            { "TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,1,0,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0},
        };

        // Describe and create the graphics pipeline state object (PSO).
        D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
        psoDesc.InputLayout = { inputElementDescs, _countof(inputElementDescs) };

        shader->Apply(&psoDesc);

        psoDesc.RasterizerState = GetDefaultRasterizerDesc();
        psoDesc.BlendState = GetDefaultBlendDesc();
        psoDesc.DepthStencilState.DepthEnable = FALSE;
        psoDesc.DepthStencilState.StencilEnable = FALSE;
        psoDesc.SampleMask = UINT_MAX;
        psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
        psoDesc.NumRenderTargets = 1;
        psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
        psoDesc.SampleDesc.Count = 1;
        FAILED(m_device->GetNativeDevice()->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&m_pipelineState)));
    }
}