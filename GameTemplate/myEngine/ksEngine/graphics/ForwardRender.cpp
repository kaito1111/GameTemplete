#include "stdafx.h"
#include "ForwardRender.h"

ForwardRender::ForwardRender() {

}
ForwardRender::~ForwardRender() {
	if (m_frameBufferRenderTargetView != nullptr) {
		m_frameBufferRenderTargetView->Release();
	}
	if (m_frameBufferDepthStencilView != nullptr) {
		m_frameBufferDepthStencilView->Release();
	}
}

void ForwardRender::Init() {
	//メインレンダリングターゲットに描かれた絵を
	//フレームバッファにコピーするためのスプライトを初期化する。
	m_copyMainRtToFrameBufferSprite.Init(
		m_mainRenderTarget.GetRenderTargetSRV(),
		FRAME_BUFFER_W,
		FRAME_BUFFER_H
	);
}

void ForwardRender::BuckupRenderTarget() {
	//レンダリングターゲットをメインに変更する。
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	ID3D11RenderTargetView* rtTbl[] = {
		m_mainRenderTarget.GetRenderTargetView()
	};
	//レンダリングターゲットの切り替え。
	d3dDeviceContext->OMSetRenderTargets(1, rtTbl, m_mainRenderTarget.GetDepthStensilView());
	if (m_mainRenderTarget.GetViewport() != nullptr) {
		//ビューポートが指定されていたら、ビューポートも変更する。
		d3dDeviceContext->RSSetViewports(1, m_mainRenderTarget.GetViewport());
	}
	//メインレンダリングターゲットをクリアする。
	float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	m_mainRenderTarget.ClearRenderTarget(clearColor);
}

void ForwardRender::LoadAndDraw() {
	//レンダリングターゲットをフレームバッファに戻す。
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();

	ID3D11RenderTargetView* rtTbl[] = {
		m_mainRenderTarget.GetRenderTargetView()
	};
	//レンダリングターゲットの切り替え。
	d3dDeviceContext->OMSetRenderTargets(1, rtTbl, m_mainRenderTarget.GetDepthStensilView());
	if (m_mainRenderTarget.GetViewport() != nullptr) {
		//ビューポートが指定されていたら、ビューポートも変更する。
		d3dDeviceContext->RSSetViewports(1, m_mainRenderTarget.GetViewport());
	}
	//ドロドロ
	m_copyMainRtToFrameBufferSprite.Draw(g_camera2D.GetViewMatrix(),g_camera2D.GetProjectionMatrix());
	m_frameBufferRenderTargetView->Release();
	m_frameBufferDepthStencilView->Release();
}