#pragma once

class VertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();

	bool Create(int numVertex, int stride, const void* pSrcVertexBuffer);

	int GetStride()const {
		return m_stride;
	}

	ID3D11Buffer*& GetBody() {
		return m_vertexBuffer;
	}

	void Release();

private:
	ID3D11Buffer* m_vertexBuffer = nullptr;
	int m_stride = 0;
};

