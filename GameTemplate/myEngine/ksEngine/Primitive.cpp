#include "stdafx.h"
#include "Primitive.h"

Primitive::Primitive()
{
}

Primitive::~Primitive()
{
	Release();
}

bool Primitive::Create(D3D_PRIMITIVE_TOPOLOGY topology, int numVertex, int vertexStride, void * pSrcVertexBuffer, int numIndex, IndexBuffer::EnIndexType indexType, void * pSrcIndexBuffer)
{
	Release();
	m_topology = topology;
	bool result = m_VertexBuffer.Create(numVertex, vertexStride, pSrcVertexBuffer);
	if (!result) {
		MessageBox(
			NULL,
			TEXT("プリミティブの作成に失敗しました"),
			TEXT("プリミティブ"),
			MB_ICONWARNING);
		return false;
	}
	if (pSrcIndexBuffer) {
		result = m_IndexBuffer.Create(numIndex, indexType, pSrcIndexBuffer);
		if (!result) {
			MessageBox(
				NULL,
				TEXT("プリミティブの作成に失敗しました"),
				TEXT("プリミティブ"),
				MB_ICONWARNING);
			return false;
		}
	}

	return true;
}

void Primitive::Draw()
{
	auto devCon = g_graphicsEngine->GetD3DDeviceContext();
	IndexBuffer::EnIndexType type = m_IndexBuffer.GetIndexType();
	devCon->IASetIndexBuffer(
		m_IndexBuffer.GetBody(),
		type == IndexBuffer::enIndexType_16 ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT,
		0
	);
	UINT offset = 0;
	UINT stride = m_VertexBuffer.GetStride();
	devCon->IASetVertexBuffers(0, 1, &m_VertexBuffer.GetBody(), &stride, &offset);
	devCon->IASetPrimitiveTopology(m_topology);
	devCon->DrawIndexed(m_IndexBuffer.GetNumIndex(), 0, 0);
}

void Primitive::Release()
{
	m_IndexBuffer.Release();
	m_VertexBuffer.Release();
}
