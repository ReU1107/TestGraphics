#pragma once
#include <cstdint>
#include "Utility/Assert.h"
#include <vector>

/*
* CommandListのUploadData()コマンドの引数に渡す。
*/

namespace Alpha
{
	class VertexBuffer;
	class IndexBuffer;
	class UniformBuffer;
	class StagingBuffer;

	enum class UploadType
	{
		Vertex,
		Index,
		Uniform,
	};

	struct UploadBuffer
	{
		union
		{
			VertexBuffer* Vertex;
			IndexBuffer* Index;
			UniformBuffer* Uniform;
		}Bind{};
		
		UploadType Type{ UploadType::Vertex };
		StagingBuffer* Staging{ nullptr };
	};

	// CPUとGPUのデータの受け渡しを担う
	class GPUDataTransfer
	{
	private:
		std::vector<UploadBuffer> mUploadBuffers{};	// Uploadするバッファ群

	public:
		GPUDataTransfer();
		~GPUDataTransfer();
		// 
		void AddVertexBuffer(VertexBuffer* vertex_buffer, StagingBuffer* staging_buffer);
		void AddIndexBuffer(IndexBuffer* index_buffer, StagingBuffer* staging_buffer);
		void AddUniformBuffer(UniformBuffer* uniform_buffer, StagingBuffer* staging_buffer);

		// 現在積んでいるアップロード予定のものをUploadし終えたら呼び出す
		void Reset();
		// Upload予定のバッファがあるか
		bool HasUpload() const;
	};

}



//class RHIResource;

//class GPUDataTransfer
//{
//private:
//	RHIResource* m_rhi;		// APIの

//	void* m_buffer;			// 
//	size_t m_size;			// サイズ
//public:
//	GPUDataTransfer();
//	~GPUDataTransfer();

//	/*
//	* Bufferの確保(一度しか呼ばれない想定)
//	*/
//	template<typename T>
//	void* AllocBuffer(uint64_t num);
//	// GPUにデータ送信
//	void Upload();

//	// newで確保したメモリにデータコピー
//	template<typename T>
//	inline T& operator[](const size_t index)
//	{
//		AssertArrayIndex(index, m_size / sizeof(T));
//		return m_buffer[index];
//	}
//};


//struct TextureInfo
//{

//};

//struct TextureInfo1D : public TextureInfo
//{
//	TextureInfo1D();
//};

//struct TextureInfo2D : public TextureInfo
//{
//	TextureInfo2D();
//};

//struct TextureInfo3D : public TextureInfo
//{
//	TextureInfo3D();
//};

//struct RenderTextureInfo : public TextureInfo
//{
//	RenderTextureInfo();
//};

//struct DepthTextureInfo : public TextureInfo
//{
//	DepthTextureInfo();
//};

//class Texture
//{
//private:
//	GPUDataTransfer m_transfer;	// 
//	TextureInfo m_info;			// 

//};

//template<typename T>
//inline void* GPUDataTransfer::AllocBuffer(uint64_t num)
//{
//	m_buffer = new T[num];
//	m_size = sizeof(T) * num;
//	return m_buffer;
//}