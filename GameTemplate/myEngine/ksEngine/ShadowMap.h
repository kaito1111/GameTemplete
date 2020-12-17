#pragma once
class SkinModel;
#include "graphics/RenderTarget.h"
class ShadowMap
{
public:
	ShadowMap();
	~ShadowMap();
	void RegistShadowCaster(SkinModel* shadowCaster)
	{
		m_shadowCasters.push_back(shadowCaster);
	}

	ID3D11ShaderResourceView* GetSRV() {
		return m_shadowMapRT.GetRenderTargetSRV();
	}
	CMatrix GetLightViewMatrox() {
		return m_lightViewMatrix;
	}
	CMatrix GetLightProjMatrix() {
		return m_lightProjMatrix;
	}
	void Init();
	void UpdateShadowMap();
	void RenderToShadowMap();

private:
	void SaveRenderTarget();
	void BackUpRenderTarget();

	//現在のレンダリングターゲットをバックアップしておく。
	ID3D11RenderTargetView* m_oldRenderTargetView = nullptr;
	ID3D11DepthStencilView* m_oldDepthStencilView = nullptr;
	//ビューポートもバックアップを取っておく。
	unsigned int m_numViewport = 1;
	D3D11_VIEWPORT m_oldViewports;
	CVector3 m_lightCameraPosition = { 0.0f,500.0f,0.0f };//ライトカメラの視点。
	CVector3 m_lightCameraTarget = { 0.0f,0.0f,0.0f }; //ライトカメラの注視点。
	CMatrix m_lightViewMatrix; //ライトビュー行列。
	CMatrix m_lightProjMatrix; //ライトプロジェクション行列。
	RenderTarget m_shadowMapRT; //シャドウマップを描画するレンダリングターゲット。
	std::vector<SkinModel*> m_shadowCasters;	//シャドウキャスターの配列。
};

