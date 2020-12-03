#pragma once
class RenderTarget
{
public:
	RenderTarget();
	~RenderTarget();

	void OffScreenRendering();
	void OnScreenRendering();

	ID3D11ShaderResourceView* GetRTSRV(){
		return m_renderTargetSRV;
	}
private:
	ID3D11RenderTargetView*		m_oldRenderTargetView;
	ID3D11DepthStencilView*		m_oldDepthStencilView;
	ID3D11Texture2D*			m_renderTargetTex = nullptr;		//!<レンダリングターゲットとなるテクスチャ。
	ID3D11RenderTargetView*		m_renderTargetView = nullptr;		//!<レンダーターゲットビュー。
	ID3D11ShaderResourceView*	m_renderTargetSRV = nullptr;		//!<レンダリングターゲットのSRV
	ID3D11Texture2D*			m_depthStencilTex = nullptr;		//!<デプスステンシルとなるテクスチャ。
	ID3D11DepthStencilView*		m_depthStencilView = nullptr;		//!<デプスステンシルビュー。
};

