#include "stdafx.h"
#include "PostEffect.h"
#include "graphics/Bloom.h"

PostEffect::PostEffect()
{
}

PostEffect::~PostEffect()
{
}

struct SVertex {
	float position[4];		//頂点座標。
	float uv[2];			//UV座標。これがテクスチャ座標
};

void PostEffect::Init()
{
	m_mainRenderTarget.Create(
		FRAME_BUFFER_W,
		FRAME_BUFFER_H,
		DXGI_FORMAT_R16G16B16A16_FLOAT
	);
	m_copyMainRtToFrameBufferSprite.Init(
		m_mainRenderTarget.GetRenderTargetSRV(),
		FRAME_BUFFER_W,
		FRAME_BUFFER_H
	);
	//頂点バッファを初期化。
	SVertex vertex[4] = {
		//頂点１
		{
			//座標　position[4]
			-1.0f,  -1.0f, 0.0f, 1.0f,
			//UV座標 uv[2]
			0.0f, 1.0f
		},
		//頂点２
		{
			//座標　position[4]
			1.0f, -1.0f, 0.0f, 1.0f,
			//UV座標 uv[2]
			1.0f, 1.0f
		},
		//頂点３
		{
			//座標　position[4]
			-1.0f,  1.0f, 0.0f, 1.0f,
			//UV座標 uv[2]
			0.0f, 0.0f
		},
		//頂点４
		{
			//座標　position[4]
			1.0f,  1.0f, 0.0f, 1.0f,
			//UV座標 uv[2]
			1.0f, 0.0f
		},
	};
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));				//構造体を0で初期化する。
	bd.Usage = D3D11_USAGE_DEFAULT;				//バッファーで想定されている読み込みおよび書き込みの方法。
												//取りあえずはD3D11_USAGE_DEFAULTでよい。
	bd.ByteWidth = sizeof(vertex);				//頂点バッファのサイズ。頂点のサイズ×頂点数となる。
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;	//これから作成するバッファが頂点バッファであることを指定する。

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertex;

	//頂点バッファの作成。
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bd, &InitData, &m_vertexBuffer);
	m_bloom.Init();
}

void PostEffect::ChangeMainRendertTarget()
{
	auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();
	deviceContext->OMGetRenderTargets(
		1,
		&m_PostEffectRenderTargetView,
		&m_PostEffectDepthStencilView
	);
	//ビューポートもバックアップを取っておく。
	unsigned int numViewport = 1;
	deviceContext->RSGetViewports(&numViewport, &m_PostEffectViewports);
	ChangeRenderTarget(
		m_mainRenderTarget.GetRenderTargetView(),
		m_mainRenderTarget.GetDepthStensilView(),
		&m_PostEffectViewports
	);
	//メインレンダリングターゲットをクリアする。
	float clearColor[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	m_mainRenderTarget.ClearRenderTarget(clearColor);
	m_copyMainRtToFrameBufferSprite.Update();
}

void PostEffect::PostRender()
{
	ChangeRenderTarget(
		m_PostEffectRenderTargetView,
		m_PostEffectDepthStencilView,
		&m_PostEffectViewports
	);
	m_copyMainRtToFrameBufferSprite.Draw(
		g_camera2D.GetViewMatrix(),
		g_camera2D.GetOrthoProjectionMatrix()
	);
	if (m_PostEffectRenderTargetView != nullptr) {
		m_PostEffectRenderTargetView->Release();
	}
	if (m_PostEffectDepthStencilView != nullptr) {
		m_PostEffectDepthStencilView->Release();
	}
}

void PostEffect::Draw()
{
	m_bloom.Draw(*this);
}

void PostEffect::DrawFullScreenQuadPrimitive(ksEngine::Shader& vsShader, ksEngine::Shader& psShader)
{
	auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();
	//プリミティブのトポロジーとして、トライアングルストリップを設定する。
	deviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	unsigned int vertexSize = sizeof(SVertex);
	unsigned int offset = 0;
	//輝度抽出用のシェーダーを設定する。
	deviceContext->VSSetShader(
		(ID3D11VertexShader*)vsShader.GetBody(), nullptr, 0
	);
	deviceContext->PSSetShader(
		(ID3D11PixelShader*)psShader.GetBody(), nullptr, 0
	);
	deviceContext->IASetInputLayout(vsShader.GetInputLayout());

	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &vertexSize, &offset);
	deviceContext->Draw(4, 0);
}