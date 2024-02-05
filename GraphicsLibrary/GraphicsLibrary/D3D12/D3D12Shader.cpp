//
//#include "D3D12Shader.h"
//
//#include "D3D12Device.h"
//#include "Utility/EnumClassFlags.h"
//
//#include "D3D12PipelineState.h"
//
//D3D12Shader::D3D12Shader(D3D12Device* device)
//	: D3D12DeviceObject(device)
//{
//
//}
//
//D3D12Shader::~D3D12Shader()
//{
//}
//
//D3D12RootSignature::D3D12RootSignature(D3D12Device* device)
//	: D3D12DeviceObject(device)
//{
//
//	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc = {};
//	rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
//	rootSignatureDesc.NumParameters = 0;
//	rootSignatureDesc.pParameters = nullptr;
//
//    ComPtr<ID3DBlob> signature;
//    ComPtr<ID3DBlob> error;
//	FAILED(D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error));
//	FAILED(m_device->GetNativeDevice()->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&m_rootSignature)));
//}
//
//D3D12RootSignature::D3D12RootSignature(D3D12Device* device, ID3DBlob* blob)
//	: D3D12DeviceObject(device)
//{
//	ComPtr<ID3DBlob> signature;
//	ComPtr<ID3DBlob> error;
//	auto hr = D3DGetBlobPart(blob->GetBufferPointer(), blob->GetBufferSize(), D3D_BLOB_ROOT_SIGNATURE, 0, &signature);
//	FAILED(m_device->GetNativeDevice()->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&m_rootSignature)));
//}
//
//D3D12RootSignature::~D3D12RootSignature()
//{
//}
//
//D3D12VertexShader::D3D12VertexShader(D3D12Device* device, std::wstring& filePath)
//	: D3D12Shader(device)
//{
//#if defined(_DEBUG)
//	// Enable better shader debugging with the graphics debugging tools.
//	UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
//#else
//	UINT compileFlags = 0;
//#endif
//	if (FAILED(D3DCompileFromFile(filePath.c_str(), nullptr, nullptr, "VSMain", "vs_5_0", compileFlags, 0, &m_blob, nullptr)))
//	{
//		int i = 0;
//	}
//
//	//auto a = new D3D12RootSignature(device, m_blob.Get());
//
//}
//
//D3D12VertexShader::~D3D12VertexShader()
//{
//}
//
//D3D12PixelShader::D3D12PixelShader(D3D12Device* device, std::wstring& filePath)
//	: D3D12Shader(device)
//{
//#if defined(_DEBUG)
//	// Enable better shader debugging with the graphics debugging tools.
//	UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
//#else
//	UINT compileFlags = 0;
//#endif
//	FAILED(D3DCompileFromFile(filePath.c_str(), nullptr, nullptr, "PSMain", "ps_5_0", compileFlags, 0, &m_blob, nullptr));
//}
//
//D3D12PixelShader::~D3D12PixelShader()
//{
//}
//
//D3D12EffectShader::D3D12EffectShader(D3D12Device* device, std::wstring& filePath, D3D12ShaderType type)
//	: D3D12Shader(device)
//	, m_vertexShader(nullptr)
//	, m_pixelShader(nullptr)
//	, m_rootSignature(nullptr)
//	, m_type(type)
//{
//#if defined(_DEBUG)
//	// Enable better shader debugging with the graphics debugging tools.
//	UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
//#else
//	UINT compileFlags = 0;
//#endif
//	if ((type & D3D12ShaderType::Vertex) != 0)
//	{
//		m_vertexShader = new D3D12VertexShader(device, filePath);
//	}
//	if ((type & D3D12ShaderType::Pixel) != 0)
//	{
//		m_pixelShader = new D3D12PixelShader(device, filePath);
//	}
//	if (S_OK == D3DGetBlobPart(m_vertexShader->GetNativeShader()->GetBufferPointer(), m_vertexShader->GetNativeShader()->GetBufferSize(), D3D_BLOB_ROOT_SIGNATURE, 0, &m_blob))
//	{
//		// ルートシグネチャ用
//		m_rootSignature = new D3D12RootSignature(device, m_blob.Get());
//	}
//}
//
//D3D12EffectShader::~D3D12EffectShader()
//{
//	delete m_rootSignature;
//	delete m_pixelShader;
//	delete m_vertexShader;
//
//}
//
//void D3D12EffectShader::Apply(D3D12_GRAPHICS_PIPELINE_STATE_DESC* info)
//{
//	info->pRootSignature = m_rootSignature->GetNativeRootSignature();
//
//	if ((m_type & D3D12ShaderType::Vertex) != 0)
//	{
//		info->VS.pShaderBytecode = m_vertexShader->GetNativeShader()->GetBufferPointer();
//		info->VS.BytecodeLength = m_vertexShader->GetNativeShader()->GetBufferSize();
//	}
//	if ((m_type & D3D12ShaderType::Pixel) != 0)
//	{
//		info->PS.pShaderBytecode = m_pixelShader->GetNativeShader()->GetBufferPointer();
//		info->PS.BytecodeLength = m_pixelShader->GetNativeShader()->GetBufferSize();
//	}
//}
//
