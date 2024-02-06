#pragma once
#include <cstdint>
#include "Utility/Assert.h"
#include <vector>

/*
* CommandList��UploadData()�R�}���h�̈����ɓn���B
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

	// CPU��GPU�̃f�[�^�̎󂯓n����S��
	class GPUDataTransfer
	{
	private:
		std::vector<UploadBuffer> mUploadBuffers{};	// Upload����o�b�t�@�Q

	public:
		GPUDataTransfer();
		~GPUDataTransfer();
		// 
		void AddVertexBuffer(VertexBuffer* vertex_buffer, StagingBuffer* staging_buffer);
		void AddIndexBuffer(IndexBuffer* index_buffer, StagingBuffer* staging_buffer);
		void AddUniformBuffer(UniformBuffer* uniform_buffer, StagingBuffer* staging_buffer);

		// ���ݐς�ł���A�b�v���[�h�\��̂��̂�Upload���I������Ăяo��
		void Reset();
		// Upload�\��̃o�b�t�@�����邩
		bool HasUpload() const;
	};

}



//class RHIResource;

//class GPUDataTransfer
//{
//private:
//	RHIResource* m_rhi;		// API��

//	void* m_buffer;			// 
//	size_t m_size;			// �T�C�Y
//public:
//	GPUDataTransfer();
//	~GPUDataTransfer();

//	/*
//	* Buffer�̊m��(��x�����Ă΂�Ȃ��z��)
//	*/
//	template<typename T>
//	void* AllocBuffer(uint64_t num);
//	// GPU�Ƀf�[�^���M
//	void Upload();

//	// new�Ŋm�ۂ����������Ƀf�[�^�R�s�[
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