#pragma once
class IndexBuffer
{
public:
	IndexBuffer();
	~IndexBuffer();

	enum EnIndexType {
		enIndexType_16,
		enIndexType_32,
	};

	bool Create(int numIndex, EnIndexType indexType, const void* pSrcIndexBuffer);

	void Release();

	EnIndexType GetIndexType() const{
		return m_indexType;
	}

	unsigned int GetNumIndex() const{
		return m_numIndex;
	}

	ID3D11Buffer* GetBody()const {
		return m_indexBuffer;
	}

	bool IsCreated() const{
		return m_IsCreated;
	}
private:
	bool m_IsCreated = false;
	ID3D11Buffer* m_indexBuffer = nullptr;
	EnIndexType m_indexType = enIndexType_16;
	unsigned int m_numIndex = 0;
};