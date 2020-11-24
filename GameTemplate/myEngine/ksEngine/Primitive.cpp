#include "stdafx.h"
#include "Primitive.h"

Primitive::Primitive()
{
}

Primitive::~Primitive()
{
	Release();
}

void Primitive::Release()
{
	m_IndexBuffer.Release();
	m_VertexBuffer.Release();
}
