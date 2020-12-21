#pragma once
#include "graphics/Shader.h"

namespace ksEngine {
	class Sprite
	{
	public:
		Sprite() {};
		~Sprite() {
			if (m_translucentBlendState != nullptr) {
				m_translucentBlendState->Release();
			}
			if (m_TextureSRV != nullptr) {
				m_TextureSRV->Release();
			}
			if (m_indexBuffer != nullptr) {
				m_indexBuffer->Release();
			}
			if (m_vertexBuffer != nullptr) {
				m_vertexBuffer->Release();
			}
			if (m_constantBuffer != nullptr) {
				m_constantBuffer->Release();
			}
		};

		/// <summary>
		/// 初期化。
		/// </summary>
		/// <param name="texFilePath">テクスチャのファイルパス</param>
		/// <param name="w">画像の幅</param>
		/// <param name="h">画像の高さ</param>
		void Init(const wchar_t* fileName, float w, float h);

		/// <summary>
		/// テクスチャのSRVを指定して初期化。
		/// </summary>
		/// <param name="srv"></param>
		/// <param name="w"></param>
		/// <param name="h"></param>
		void Init(ID3D11ShaderResourceView* srv, float w, float h);

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

		void SetPivot(const CVector2& pivot) {
			m_pivot = pivot;
		}

		void Update();
		void Draw(const CMatrix& viewMatrix, const CMatrix& projMatrix);
	
	private:
		/// <summary>
		/// 初期化の共通処理。
		/// </summary>
		void InitCommon(float w, float h);

		void CreateVertexBuffer(float w, float h);
		void CreateIndexBuffer();
		void CreateConstantBuffer();
		void InitTranslucentBlendState();
		void InitShader();
		void CreateFromDDSTextureFromFile(const wchar_t* fileName);
		void SetVertexBuffer();
		void SetWorld();
		void SetWVP(const CMatrix & viewMatrix, const CMatrix & projMatrix);
		void ConstantBuffer();
		void SetShader();
		void InitSamplerState();
	private:
		bool IsCreated = false;
		CVector3 m_position = CVector3::Zero();
		CQuaternion m_rotation = CQuaternion::Identity();
		CVector3 m_scale = CVector3::One();
		CVector2 m_pivot = CVector2::Zero();
		CMatrix m_world = CMatrix::Identity();
		Shader m_ps;
		Shader m_vs;
		CVector4 m_mulColor = CVector4::White();
		ID3D11DeviceContext* m_deviceContext = nullptr;
		ID3D11Buffer* m_constantBuffer = nullptr;
		ID3D11Buffer* m_vertexBuffer = nullptr;
		ID3D11Buffer* m_indexBuffer = nullptr;
		ID3D11ShaderResourceView* m_TextureSRV = nullptr;
		ID3D11BlendState* m_translucentBlendState = nullptr;
		float m_alpha = 1.0f;
		ID3D11SamplerState*			m_samplerState = NULL;					//サンプラステート。
		CVector2 m_Size = CVector2::Zero();
	};
}