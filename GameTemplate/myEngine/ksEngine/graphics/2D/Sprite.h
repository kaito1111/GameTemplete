#pragma once
#include "graphics/Shader.h"

namespace ksEngine {
	class Sprite
	{
	public:
		Sprite() {};
		~Sprite() {};

		void Init(const wchar_t* fileName/*, float w, float h*/);

		void SetTexture(ID3D11ShaderResourceView& tex) {
			m_TextureSRV = &tex;
		}

		void SetMulColor(const CVector4& color) {
			m_mulColor = color;
		}

		void SetPosition(const CVector3& pos) {
			m_position = pos;
		}

		void SetRotation(const CQuaternion& rot) {
			m_rotation = rot;
		}

		void SetScale(const CVector3& scale) {
			m_scale = scale;
		}

		void Update();
		void Draw(const CMatrix& viewMatrix, const CMatrix& projMatrix);
	
	private:
		void CreateVertexBuffer();
		//void CreateIndexBuffer();
		void CreateConstantBuffer();
		void InitShader();
		void CreateFromDDSTextureFromFile(const wchar_t* fileName);
		void SetVertexBuffer();
		void SetWorld();
		void SetWVP(const CMatrix & viewMatrix, const CMatrix & projMatrix);
		void ConstantBuffer();
		void SetShader();
	private:
		bool IsCreated = false;
		CVector3 m_position = CVector3::Zero();
		CQuaternion m_rotation = CQuaternion::Identity();
		CVector3 m_scale = CVector3::One();
		CMatrix m_world = CMatrix::Identity();
		Shader m_ps;
		Shader m_vs;
		CVector4 m_mulColor = CVector4::White();
		ID3D11DeviceContext* m_deviceContext = nullptr;
		ID3D11Buffer* m_constantBuffer = nullptr;
		ID3D11Buffer* m_vertexBuffer = nullptr;
		//ID3D11Buffer* m_indexBuffer = nullptr;
		ID3D11ShaderResourceView* m_TextureSRV = nullptr;
	};
}