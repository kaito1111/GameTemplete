#include "stdafx.h"
#include "graphics/GPUBuffer/VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
}

VertexBuffer::~VertexBuffer()
{
	Release();
}

bool VertexBuffer::Create(int numVertex, int stride, const void * pSrcVertexBuffer)
{
	Release();
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = numVertex * stride;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA InitDate;
	ZeroMemory(&InitDate, sizeof(InitDate));
	InitDate.pSysMem = pSrcVertexBuffer;

	HRESULT hr = g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bd, &InitDate, &m_vertexBuffer);
	if (FAILED(hr)) {
		return false;
	}
	m_stride = stride;
	return true;
	return true;
}

void VertexBuffer::Release()
{
	if (m_vertexBuffer != nullptr) {
		m_vertexBuffer->Release();
		m_vertexBuffer = nullptr;
	}
}
