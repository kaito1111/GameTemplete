#include "stdafx.h"
#include "IndexBuffer.h"

IndexBuffer::IndexBuffer()
{
}

IndexBuffer::~IndexBuffer()
{
	Release();
}

bool IndexBuffer::Create(int numIndex, EnIndexType indexType, const void * pSrcIndexBuffer)
{
	Release();

	int stride = 0;
	if (indexType == enIndexType_16) {
		//16bit
		stride = 2;
	}
	else {
		//32bit
		stride = 4;
	}
	m_indexType = indexType;
	m_numIndex = numIndex;
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.StructureByteStride = stride;
	bd.ByteWidth = stride * numIndex;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = pSrcIndexBuffer;

	HRESULT hr = g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bd, &InitData, &m_indexBuffer);
	if (FAILED(hr)) {
		return false;
	}
	m_IsCreated = true;
	return true;
}

void IndexBuffer::Release()
{
	if (m_indexBuffer) {
		m_indexBuffer->Release();
		m_indexBuffer = nullptr;
	}
	m_IsCreated = false;
}
