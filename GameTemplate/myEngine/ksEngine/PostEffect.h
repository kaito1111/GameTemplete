#pragma once
#include "graphics/ChangeRenderTarget.h"
#include "graphics/Bloom.h"
#include "graphics/2D/Sprite.h"
class PostEffect
{
public:
	PostEffect();
	~PostEffect();

	//初期化
	void Init();
	//レンダーターゲットを切り替える
	void ChangeMainRendertTarget();
	//書かれたものをドローする
	void PostRender();

	void Draw();
	RenderTarget* GetMainRenderTarget() {
		return &m_mainRenderTarget;
	}
	void DrawFullScreenQuadPrimitive(ksEngine::Shader& vsShader, ksEngine::Shader& psShader);
private:
	Bloom	m_bloom;	//ブルーム。
						//フルスクリーン描画用のメンバ変数。
	ID3D11Buffer*	m_vertexBuffer = nullptr;		//頂点バッファ。
	D3D11_VIEWPORT m_mainViewports;			//変更前のビューポート。
	RenderTarget m_mainRenderTarget;
	ksEngine::Sprite m_copyMainRtToFrameBufferSprite;
	D3D11_VIEWPORT m_PostEffectViewports;			//ポストエフェクト用のビューポート。
	ID3D11RenderTargetView* m_PostEffectRenderTargetView = nullptr;	//ポストエフェクト用のレンダリングターゲットビュー。
	ID3D11DepthStencilView* m_PostEffectDepthStencilView = nullptr;	//ポストエフェクト用のデプスステンシルビュー。
};

