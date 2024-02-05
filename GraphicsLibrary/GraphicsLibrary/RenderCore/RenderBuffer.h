#pragma once
#include <cstdint>

namespace Alpha
{
	class RHIBuffer;

	struct BufferInfo
	{
		uint32_t Stride;	// 
		uint32_t Count;		// 

	};

	struct VertexBufferInfo : public BufferInfo
	{
		VertexBufferInfo();
	};

	struct IndexBufferInfo : public BufferInfo
	{
		IndexBufferInfo();
	};

	struct UniformBufferInfo : public BufferInfo
	{
		UniformBufferInfo();
	};

	struct ConstantBufferInfo : public BufferInfo
	{
		ConstantBufferInfo();
	};
	// 
	struct StagingBufferInfo : public BufferInfo
	{
		StagingBufferInfo();
	};

	/*
	* Uniform,Constant 同じように使えますが、
	* Uniformは少ないサイズを頻繁に更新する
	* Constantは大きいサイズをあまり更新しないイメージで使ってください。
	* そこまでこだわらなくていいです。
	*/

	//class RenderBuffer
	//{
	//private:
	//	RHIBuffer* mRHI{ nullptr };		// 
	//	BufferInfo mInfo{};				// 

	//public:
	//	RenderBuffer();
	//	~RenderBuffer();

	//};

	//class VertexBuffer : public RenderBuffer
	//{
	//public:
	//	VertexBuffer();
	//	~VertexBuffer();
	//};


	//class StagingBuffer : public RenderBuffer
	//{
	//private:
	//	void* mTransferData{ nullptr };
	//public:
	//	StagingBuffer();
	//	~StagingBuffer();

	//};

}