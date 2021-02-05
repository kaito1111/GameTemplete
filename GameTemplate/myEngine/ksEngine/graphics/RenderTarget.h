#pragma once
class RenderTarget
{
public:
	RenderTarget();
	~RenderTarget();

	void Create(UINT w,UINT h, DXGI_FORMAT format);
	void SaveRenderTarget();
	void BackUpRenderTarget();

	/// <summary>
	/// レンダリングターゲットとデプスステンシルのクリア。
	/// </summary>
	/// <param name="clearColor">クリアカラー</param>
	void ClearRenderTarget(float* clearColor);

	/// <summary>
	/// レンダリングターゲットビューを取得。
	/// </summary>
	/// <returns>レンダリングターゲットビュー</returns>
	ID3D11RenderTargetView* GetRenderTargetView()
	{
		return m_renderTargetView;
	}

	/// <summary>
	/// デプスステンシルビューを取得。
	/// </summary>
	/// <returns>デプスステンシルビュー</returns>
	ID3D11DepthStencilView* GetDepthStensilView()
	{
		return m_depthStencilView;
	}

	/// <summary>
	/// レンダリングターゲットのSRVを取得。
	/// </summary>
	/// <returns>レンダリングターゲットのSRV</returns>
	ID3D11ShaderResourceView* GetRenderTargetSRV()
	{
		return m_renderTargetSRV;
	}
	/// <summary>
	/// ビューポートの取得。
	/// </summary>
	/// <returns>ビューポート</returns>
	D3D11_VIEWPORT* GetViewport()
	{
		return &m_viewport;
	}
	float GetWidth() {
		return m_width;
	}
	float GetHeight() {
		return m_height;
	}
private:
	ID3D11RenderTargetView*		m_oldRenderTargetView;
	ID3D11DepthStencilView*		m_oldDepthStencilView;
	ID3D11Texture2D*			m_renderTargetTex = nullptr;		//!<レンダリングターゲットとなるテクスチャ。
	ID3D11RenderTargetView*		m_renderTargetView = nullptr;		//!<レンダーターゲットビュー。
	ID3D11ShaderResourceView*	m_renderTargetSRV = nullptr;		//!<レンダリングターゲットのSRV
	ID3D11Texture2D*			m_depthStencilTex = nullptr;		//!<デプスステンシルとなるテクスチャ。
	ID3D11DepthStencilView*		m_depthStencilView = nullptr;		//!<デプスステンシルビュー。
	D3D11_VIEWPORT				m_viewport;							//!<ビューポート。
	float m_width = 0;
	float m_height = 0;
};

