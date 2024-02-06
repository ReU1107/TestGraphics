#include "GPUDataTransfer.h"
#include "RHI/RHIResource.h"
#include "Utility/SmartPointer.h"
#include "Utility/Assert.h"

namespace Alpha
{
	GPUDataTransfer::GPUDataTransfer()
	{
	}

	GPUDataTransfer::~GPUDataTransfer()
	{
	}

	void GPUDataTransfer::AddVertexBuffer(VertexBuffer* vertex_buffer, StagingBuffer* staging_buffer)
	{
		UploadBuffer upload = {};
		upload.Bind.Vertex = vertex_buffer;
		upload.Staging = staging_buffer;
		upload.Type = UploadType::Vertex;
		mUploadBuffers.push_back(upload);
	}

	void GPUDataTransfer::AddIndexBuffer(IndexBuffer* index_buffer, StagingBuffer* staging_buffer)
	{
		UploadBuffer upload = {};
		upload.Bind.Index = index_buffer;
		upload.Staging = staging_buffer;
		upload.Type = UploadType::Index;
		mUploadBuffers.push_back(upload);
	}

	void GPUDataTransfer::AddUniformBuffer(UniformBuffer* uniform_buffer, StagingBuffer* staging_buffer)
	{
		UploadBuffer upload = {};
		upload.Bind.Uniform = uniform_buffer;
		upload.Staging = staging_buffer;
		upload.Type = UploadType::Uniform;
		mUploadBuffers.push_back(upload);
	}

	void GPUDataTransfer::Reset()
	{
		mUploadBuffers.clear();
	}

	bool GPUDataTransfer::HasUpload() const
	{
		// êœÇÒÇ≈Ç¢ÇÈÉRÉ}ÉìÉhÇ™Ç»Ç¢Ç»ÇÁ
		if (mUploadBuffers.size() < 1)
			return false;

		return true;
	}
}