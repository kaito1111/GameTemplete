#pragma once
/*!
 *@brief	グラフィックスエンジン。
 */
#include "ShadowMap.h"
#include "PostEffect.h"
#include "Effect/EffectEngine.h"
class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();
	/*!
	 *@brief	初期化。
	 *@param[in]	hWnd		ウィンドウハンドル。
	 */
	void Init(HWND hWnd);
	/*!
	 *@brief	解放。
	 */
	void Release();
	/*!
	 *@brief	D3D11デバイスを取得。
	 */
	ID3D11Device* GetD3DDevice()
	{
		return m_pd3dDevice;
	}

	ID3D11RasterizerState* GetRS()
	{
		return m_rasterizerState;
	}
	/*!
	 *@brief	D3D11デバイスコンテキストを取得。
	 */
	ID3D11DeviceContext* GetD3DDeviceContext()
	{
		return m_pd3dDeviceContext;
	}
	/*!
	 *@brief	描画開始。
	 */
	void BegineRender();
	/*!
	 *@brief	描画終了。
	 */
	void EndRender();

	ShadowMap* GetShadowMap() {
		return &m_ShadowMap;
	}
	PostEffect* GetPostEffect() {
		return &m_PostEffect;
	}
	ID3D11DepthStencilView* GetDepthStencilView() {
		return m_depthStencilView;
	}
	ID3D11BlendState*GetBlendState() {
		return m_BlendState;
	}

	EffectEngine& GetEffectEngine() {
		return m_effectEngine;
	}
private:
	D3D_FEATURE_LEVEL		m_featureLevel;				//Direct3D デバイスのターゲットとなる機能セット。
	ID3D11Device*			m_pd3dDevice = NULL;		//D3D11デバイス。
	IDXGISwapChain*			m_pSwapChain = NULL;		//スワップチェイン。
	ID3D11DeviceContext*	m_pd3dDeviceContext = NULL;	//D3D11デバイスコンテキスト。
	ID3D11RenderTargetView* m_backBuffer = NULL;		//バックバッファ。
	ID3D11RasterizerState*	m_rasterizerState = NULL;	//ラスタライザステート。
	ID3D11Texture2D*		m_depthStencil = NULL;		//デプスステンシル。
	ID3D11DepthStencilView* m_depthStencilView = NULL;	//デプスステンシルビュー。
	ShadowMap m_ShadowMap;
	PostEffect m_PostEffect;
	ID3D11BlendState* m_BlendState = nullptr;
	EffectEngine			m_effectEngine;								//!<エフェクトエンジン。
};

extern GraphicsEngine* g_graphicsEngine;			//グラフィックスエンジン