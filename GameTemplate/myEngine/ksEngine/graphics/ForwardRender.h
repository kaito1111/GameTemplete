#pragma once
class ForwardRender
{
public:
	ForwardRender();
	~ForwardRender();

	void Init();
	void BuckupRenderTarget();
	//バックアップしたものを読みこむ
	//ついでにフォワードレンダーもする
	void LoadAndDraw();
private:
	RenderTarget m_mainRenderTarget;		//メインレンダリングターゲット。
	Sprite m_copyMainRtToFrameBufferSprite;
	D3D11_VIEWPORT m_frameBufferViewports;			//フレームバッファのビューポート。
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//フレームバッファのレンダリングターゲットビュー。
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//フレームバッファのデプスステンシルビュー。
};