#pragma once

#include "graphics/GPUBuffer/VertexBuffer.h"
#include "graphics/GPUBuffer/IndexBuffer.h"

class Primitive
{
public:
	Primitive();
	~Primitive();

	bool Create(
		D3D_PRIMITIVE_TOPOLOGY topology,
		int numVertex,
		int vertexStride,
		void* pSrcVertexBuffer,
		int numIndex,
		IndexBuffer::EnIndexType indexType,
		void* pSrcIndexBuffer
	);

	void Release();
	VertexBuffer& GetVertexBuffer() {
		return m_VertexBuffer;
	}
private:
	VertexBuffer m_VertexBuffer;
	IndexBuffer	 m_IndexBuffer;
	D3D_PRIMITIVE_TOPOLOGY m_topology;
};